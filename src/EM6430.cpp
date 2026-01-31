#include <Arduino.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>

#include "traffic.h"
#include "EM6430.h"

/*
 * BUFFER[0] : Transmit buffer (Modbus command frame)
 * BUFFER[1] : Receive buffer  (Modbus response frame)
 *
 * Static pointer array shared across EM6430 instances
 */
uint8_t* EM6430::BUFFER[2] = { NULL };

/*
 * Default constructor
 */
EM6430::EM6430()
{
}

/*
 * Initialize serial communication with the EM6430 energy meter
 *
 * baud_rate : Must match the configured baud rate of the EM6430 meter
 */
void EM6430::begin(uint32_t baud_rate)
{
    // Initialize UART with specified baud rate and data packet configuration
    Serial.begin(baud_rate, EM6430_Data_Pack_Config);
}

/*
 * Send a Modbus RTU command to the EM6430 meter
 *
 * command : Index of the command (maps to register address in PROGMEM table)
 * dev_id  : Modbus slave ID of the energy meter (1–254)
 */
void EM6430::EM6430_Command(uint8_t command, uint8_t dev_id)
{
    uint8_t j;

    // Allocate memory for command buffer
    BUFFER[0] = (uint8_t*)malloc(command_buff_size * sizeof(uint8_t));

    // Clear transmit buffer
    for (int i = 0; i < command_buff_size; i++)
    {
        BUFFER[0][i] = 0x00;
    }

    /*
     * Copy command frame from PROGMEM table
     * COMMAND table contains predefined Modbus frames
     */
    for (j = 1; j < 9; j++)
    {
        BUFFER[0][j] = pgm_read_byte_near(COMMAND + command + j);
    }

    /*
     * Device ID handling (Modbus slave address)
     * Masking is done for safety, but value is written directly
     */
    dev_id >> 4 & 0x0F;
    dev_id & 0x0F;

    // Send device ID first
    Serial.write(dev_id);

    // Send remaining Modbus command bytes
    for (int i = 1; i < 8; i++)
    {
        Serial.write(BUFFER[0][i]);
    }

    // Free receive buffer if previously allocated
    free(BUFFER[1]);
}

/*
 * Read response data from EM6430 meter and convert it to float
 *
 * Returns:
 *   float value representing the requested electrical parameter
 */
float EM6430::EM6430_Data()
{
    float x = 0;

    // Allocate memory for response buffer
    BUFFER[1] = (uint8_t*)malloc(data_buff_size * sizeof(uint8_t));

    // Clear receive buffer
    for (int i = 0; i < data_buff_size; i++)
    {
        BUFFER[1][i] = 0x00;
    }

    // Wait until complete Modbus response is available
    while (Serial.available() < 9);

    // Read Modbus response bytes
    for (int i = 0; i < 9; i++)
    {
        BUFFER[1][i] = Serial.read();
    }

    // Flush remaining serial data
    Serial.flush();

    /*
     * Convert received bytes into float
     * EM6430 sends data in big-endian format
     */
    ((byte*)&x)[8] = BUFFER[1][0];
    ((byte*)&x)[7] = BUFFER[1][1];
    ((byte*)&x)[6] = BUFFER[1][2];
    ((byte*)&x)[5] = BUFFER[1][3];
    ((byte*)&x)[4] = BUFFER[1][4];
    ((byte*)&x)[3] = BUFFER[1][5];
    ((byte*)&x)[2] = BUFFER[1][6];
    ((byte*)&x)[1] = BUFFER[1][7];
    ((byte*)&x)[0] = BUFFER[1][8];

    // Free receive buffer
    free(BUFFER[1]);

    return x;
}
