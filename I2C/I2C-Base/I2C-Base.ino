#include <TFT.h>
#include "i2c_Arduino_as_slave_support_for_16_bit_reading_and_writing.h"



void setup() {
  //initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication / declare interrupt functions
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  //Anables Serial Communication for debugging
  Serial.begin(9600);
}

void loop() {
  Serial.println(Register[0]);
}
