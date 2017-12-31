//Bluetooth zeug
#include "Bluetooth.h"

#define STATE_PIN -1
#define ERROR_PIN 13
#define VALUE_COUNT 1
//variables

int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];

Bluetooth *Slave;



 //Example for pinNo. later from PinNo-class
int buttonUp = 49;
int buttonDown = 53;
int buttonRight = 50;
int buttonLeft = 52;
int buttonBack = 51;
int buttonCertify = 48;

#define FACTOR_UP 2
#define FACTOR_DOWN 3
#define FACTOR_RIGHT 5
#define FACTOR_LEFT 7
#define FACTOR_BACK 11
#define FACTOR_CERTIFY 13

void setup()
{
  Serial.begin(9600); 
  //Serial1.begin(38400);//doesent work any longer directly connected with computer

  pinMode(buttonUp,INPUT);
  pinMode(buttonDown,INPUT);
  pinMode(buttonRight,INPUT);
  pinMode(buttonLeft,INPUT);
  pinMode(buttonBack,INPUT);
  pinMode(buttonCertify,INPUT);

  Slave = new Bluetooth(false, ERROR_PIN, STATE_PIN, SERIAL_ONE, VALUE_COUNT);

}

void loop()
{
  int transmit = 1;
  if(digitalRead(buttonUp))
  {
    transmit *= FACTOR_UP;
  }
  if(digitalRead(buttonDown))
  {
    transmit *= FACTOR_DOWN;
  }
  if(digitalRead(buttonRight))
  {
      transmit *= FACTOR_RIGHT;
  }
  if(digitalRead(buttonLeft))
  {
      transmit *= FACTOR_LEFT;
  }
  if(digitalRead(buttonBack))
  {
      transmit *= FACTOR_BACK;
  }
  if(digitalRead(buttonCertify))
  {
      transmit *= FACTOR_CERTIFY;
  }
  Slave->setWrite(0, transmit);
  Slave->update();
//  Serial.println(transmit);
  delay(25);
 }
