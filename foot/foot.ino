#include "Bluetooth.h"

#define STATE_PIN   -1
#define ERROR_PIN   13
#define VALUE_COUNT 2

//variables
double ppm = 0; //parts per million of gas
double Temp = 0;//sourrounding Temp

//Constants
const double ppmConstant = 1;
const double TemperaturConstant = 0.48828125;

//Pins
const int PPM_Pin = 14;
const int temp_Pin = 15;

//Bluetooth
Bluetooth *Slave;
int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];


//
// Parts per million part
//
void ppmMeasure(){
  ppm = analogRead(PPM_Pin);
  ppm = ppm * ppmConstant;
  Slave->setWrite(0,ppm);
}

void ppm_debug_out(){
  ppm = analogRead(PPM_Pin);
  Serial.println(ppm);
}

//
//  Tempreture part
//
void TempMeasure(){
  Temp = analogRead(temp_Pin);
  Temp = Temp * TemperaturConstant *100; //the 100 comes from the fact that i2c dooes not know about digits after this but i still want to transfer it
  Slave->setWrite(1,Temp);
}

void temp_debug_out(){
  Temp = analogRead(temp_Pin);
  Temp = Temp * TemperaturConstant;
  Serial.println(Temp);
}

//
//  Microcontroller Stuff + main loop
//

void setup()
{
  //enable for debug_out
  //Serial.beginn(9600);
  Slave = new Bluetooth(false, ERROR_PIN, STATE_PIN, SERIAL_THREE, VALUE_COUNT);
}

void loop()
{
  TempMeasure();
  ppmMeasure();
  Slave->write();
}
