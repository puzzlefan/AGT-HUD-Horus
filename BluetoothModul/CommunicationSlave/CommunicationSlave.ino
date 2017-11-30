#include "Bluetooth.h"

#define STATE_PIN 0
#define ERROR_PIN 13
#define VALUE_COUNT 2
//variables

int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];

Bluetooth *Slave;

void setup() {
  Slave = new Bluetooth(false, ERROR_PIN, STATE_PIN, SERIAL_ONE, VALUE_COUNT);
}

void loop() {
  Slave->update();
  Slave->setWrite(0,analogRead(0));
  Slave->setWrite(1,analogRead(0));
}

void something(int val)//does something with the Data which has been archived
{
  Serial.print("out: ");
  Serial.println(val);
}
