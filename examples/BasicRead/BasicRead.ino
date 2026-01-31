#include <EM6430.h>

EM6430 meter;

void setup()
{
  Serial.begin(9600);
  meter.begin(9600);
}

void loop()
{
  meter.EM6430_Command(VLL, 1);
  float voltage = meter.EM6430_Data();

  Serial.print("Voltage: ");
  Serial.println(voltage);

  delay(1000);
}
