#include "Bluetooth.h"

#define STATE_PIN -1
#define ERROR_PIN 13
#define VALUE_COUNT 2
//variables

int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];

Bluetooth *Master;

void setup() {
  Master = new Bluetooth(true, ERROR_PIN, STATE_PIN, SERIAL_ONE, VALUE_COUNT);
}

void loop() {
  Master->read();
  Serial.print("PPM: ");
  Serial.println(Master->getRead(0));
  Serial.print("Tmp in C: ");
  Serial.println(Master->getRead(1));
  delay(endDelay);
}

int something()//getting some data to send
{
  return analogRead(0);
}
