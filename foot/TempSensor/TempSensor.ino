#include <TFT.h>
#include <Wire.h>

double Temp = 0;
double TemperaturKonstante = 0.48828125;

void setup() {
  //initialize i2c as slave

  //Anables Serial Communication for debugging
  Serial.begin(9600);
}

void TempMeasure(){
  Temp = analogRead(15);
  Temp = Temp * TemperaturKonstante *100; //the 100 comes from the fact that i2c dooes not know about digits after this but i still want to transfer it
  Serial.println(Temp);
}

void debug_out(){
  Temp = analogRead(15);
  Temp = Temp * TemperaturKonstante;
  Serial.println(Temp);
}

void loop() {
  // put your main code here, to run repeatedly:
  TempMeasure();
  //Serial.println(Register[0]);
}
