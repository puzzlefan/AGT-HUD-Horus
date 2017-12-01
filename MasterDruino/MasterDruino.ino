#include "Bluetooth.h"

#define ERROR_PIN   13 //LED could blink in case of error

#define STATE_FOOT  -1//Indication pin Foot Bluetooth has a connection
#define STATE_ARM   -1//Indication pij Arm Bluetooth has a connection

#define VALUE_COUNT_FOOT  2
#define VALUE_COUNT_ARM   1

Bluetooth *MasterFoot, *MasterArm;

void setup() {
  MasterFoot = new Bluetooth(true, ERROR_PIN, STATE_FOOT, SERIAL_ONE, VALUE_COUNT);
  MasterArm = new Bluetooth(true, ERROR_PIN, STATE_ARM, SERIAL_TWO, VALUE_COUNT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
