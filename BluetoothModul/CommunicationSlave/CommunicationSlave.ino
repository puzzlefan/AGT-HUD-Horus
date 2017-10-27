#include "Bluetooth.h"

#define STATE_PIN 0
#define EN_PIN 2
#define ERROR_PIN 13
#define VALUE_COUNT 1
//variables

int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];

Bluetooth Slave(false, ERROR_PIN, EN_PIN, STATE_PIN, VALUE_COUNT);

void setup() {

}

void loop() {
  Slave.read();
  something(Slave.getRead(0));
}

void something(int val)//does something with the Data which has been archived
{
  Serial.print("out: ");
  Serial.println(val);
}
