#include "Arduino.h"
#include <avr/pgmspace.h>

#ifndef EM6430_h
#define EM6430_h

/*
 * Command Index Definitions
 * -------------------------
 * Each macro represents an offset into the COMMAND[] table
 * defined in traffic.h.
 *
 * The numeric value corresponds to the starting byte index
 * of a specific Modbus RTU command frame stored in PROGMEM.
 *
 * These indices are used by EM6430_Command() to select
 * which electrical parameter to read from the meter.
 */

/* ---------------- Current ---------------- */

/* Average current (3-phase) */
#ifndef A
#define A   0
#endif

/* Current – Phase 1 */
#ifndef A1
#define A1  8
#endif

/* Current – Phase 2 */
#ifndef A2
#define A2  16
#endif

/* Current – Phase 3 */
#ifndef A3
#define A3  24
#endif

/* ---------------- Voltage ---------------- */

/* Line-to-line average voltage */
#ifndef VLL
#define VLL 32
#endif

/* Line-to-neutral voltage */
#ifndef VLN
#define VLN 40
#endif

/* Phase 1 to Phase 2 voltage */
#ifndef V12
#define V12 48
#endif

/* Phase 2 to Phase 3 voltage */
#ifndef V23
#define V23 56
#endif

/* Phase 3 to Phase 1 voltage */
#ifndef V31
#define V31 64
#endif

/* Phase 1 to neutral voltage */
#ifndef V1
#define V1  72
#endif

/* Phase 2 to neutral voltage */
#ifndef V2
#define V2  80
#endif

/* Phase 3 to neutral voltage */
#ifndef V3
#define V3  88
#endif

/* ---------------- Active Power ---------------- */

/* Total active power */
#ifndef W
#define W   96
#endif

/* Active power – Phase 1 */
#ifndef W1
#define W1  104
#endif

/* Active power – Phase 2 */
#ifndef W2
#define W2  112
#endif

/* Active power – Phase 3 */
#ifndef W3
#define W3  120
#endif

/* ---------------- Reactive Power ---------------- */

/* Total reactive power */
#ifndef VAR
#define VAR 128
#endif

/* Reactive power – Phase 1 */
#ifndef VAR1
#define VAR1 136
#endif

/* Reactive power – Phase 2 */
#ifndef VAR2
#define VAR2 144
#endif

/* Reactive power – Phase 3 */
#ifndef VAR3
#define VAR3 152
#endif

/* ---------------- Apparent Power ---------------- */

/* Total apparent power */
#ifndef VA
#define VA  160
#endif

/* Apparent power – Phase 1 */
#ifndef VA1
#define VA1 168
#endif

/* Apparent power – Phase 2 */
#ifndef VA2
#define VA2 176
#endif

/* Apparent power – Phase 3 */
#ifndef VA3
#define VA3 184
#endif

/* ---------------- Power Factor ---------------- */

/* Average power factor */
#ifndef PF
#define PF  192
#endif

/* Power factor – Phase 1 */
#ifndef PF1
#define PF1 200
#endif

/* Power factor – Phase 2 */
#ifndef PF2
#define PF2 208
#endif

/* Power factor – Phase 3 */
#ifndef PF3
#define PF3 216
#endif

/* ---------------- Frequency ---------------- */

/* Line frequency in Hz */
#ifndef Freq
#define Freq 224
#endif

/* ---------------- Energy ---------------- */

/* Forward apparent energy (VAh) */
#ifndef FwdVAh
#define FwdVAh 232
#endif

/* Forward active energy (Wh) */
#ifndef FwdWh
#define FwdWh 240
#endif

/* ---------------- Communication Settings ---------------- */

/*
 * UART data format for EM6430:
 * 8 data bits, Even parity, 1 stop bit
 */
#define EM6430_Data_Pack_Config SERIAL_8E1

/* Size of Modbus command frame (excluding slave ID) */
#define command_buff_size 7

/* Size of Modbus response data payload */
#define data_buff_size 8

#endif /* EM6430_h */

/*
 * EM6430 Class
 * ------------
 * Provides a simple Arduino-style interface to communicate
 * with the EM6430 three-phase energy meter over Modbus RTU.
 */
class EM6430
{
  public:
    /*
     * Constructor
     */
    EM6430();

    /*
     * Initialize serial communication with the meter
     *
     * baud_rate : UART baud rate (must match meter setting)
     */
    void begin(uint32_t baud_rate);

    /*
     * Send a Modbus command to the EM6430
     *
     * command : One of the command macros defined above (A, VLL, W, etc.)
     * dev_id  : Modbus slave ID (1–254)
     */
    void EM6430_Command(uint8_t command, uint8_t dev_id);

    /*
     * Read response data from the meter
     *
     * Returns:
     *   Floating-point value of the requested parameter
     */
    float EM6430_Data(void);

  private:
    /*
     * BUFFER[0] : Transmit buffer
     * BUFFER[1] : Receive buffer
     */
    static uint8_t* BUFFER[2];

    /* Internal command buffer (reserved for future use) */
    static int Command_Buffer[command_buff_size];

    /* Internal data buffer (reserved for future use) */
    static int Data_Buffer[data_buff_size];
};
