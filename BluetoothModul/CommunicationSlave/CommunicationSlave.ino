#include "Bluetooth.h"

#define STATE_PIN 0
#define ERROR_PIN 13
#define VALUE_COUNT 1
//variables

int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];

Bluetooth *Slave;

void setup() {
  Slave = new Bluetooth(false, ERROR_PIN, STATE_PIN, VALUE_COUNT);
}

void loop() {
  Slave->read();
  something(Slave->getRead(0));
}

void something(int val)//does something with the Data which has been archived
{
  Serial.print("out: ");
  Serial.println(val);
}
