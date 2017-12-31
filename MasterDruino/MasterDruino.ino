#include "Bluetooth.h"
#include "i2c_Arduino_as_slave_support_for_16_bit_reading_and_writing.h"

#define ERROR_PIN   13 //LED could blink in case of error

#define STATE_FOOT  -1//Indication pin Foot Bluetooth has a connection
#define STATE_ARM   -1//Indication pin Arm Bluetooth has a connection
#define STATE_PI    -1//indicates connectiopn to pi

#define VALUE_COUNT_FOOT  2
#define VALUE_COUNT_ARM   1
#define VALUE_COUT_PI     6

Bluetooth *MasterFoot, *MasterArm;

//pins
int Lampe = 13;

void setup() {
  //Anables Serial Communication for debugging
  Serial.begin(9600);
  //BT
  MasterFoot = new Bluetooth(true, ERROR_PIN, STATE_FOOT, SERIAL_ONE, VALUE_COUNT_FOOT);
  delay(endDelay);
  MasterArm = new Bluetooth(true, ERROR_PIN, STATE_ARM, SERIAL_TWO, VALUE_COUNT_ARM);

  //I2C
  //initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication / declare interrupt functions
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  //ensures all is set up for use of i2c
  I2CSetup();

  //Pins
  pinMode(Lampe,OUTPUT);
  pinMode(12,OUTPUT);


}

//Register usage table
/*
* 0 = Buttons
* 1 = Temp Foot
* 2 = Temp Head
* 3 = PPM Foot
* 4 = PPM Head
* 5 = lamp on/off
*/

void loop() {
  MasterFoot->update();
  MasterArm->update();

  Register[0] = MasterArm->getRead(0);//gets factor of button primes
  Register[1] = MasterFoot->getRead(1);//gets temp of foot multiplaid by 100 so we dont luse the digits after , directly
  Register[2] = random(0,255);//simulates hear read out of Tempreture
  Register[3] = MasterFoot->getRead(0);//gets ppm foot
  Register[4] = random(0,255);//simulates hear read out of ppm
  if(Register[5]==1)
  {
    digitalWrite(Lampe,HIGH);
  }
  else
  {
    digitalWrite(Lampe,LOW);
  }
//  delay(endDelay);
}
