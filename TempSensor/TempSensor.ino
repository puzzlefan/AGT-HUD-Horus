#include <TFT.h>

double Temp = 0;
double TemperaturKonstante = 0.48828125;

int i2c_Data[2];
/*
 * Index table
 * 0 == Temp
 */
int tempin = 0;

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void TempMeasure(){
  Temp = analogRead(0);
  Temp = Temp * TemperaturKonstante *100; //the 100 comes from the fact that i2c dooes not know about digits after this but i still want to transfer it
  i2c_Data[tempin] = int(Temp);
}

void debug_out(){
  Temp = analogRead(0);
  Temp = Temp * TemperaturKonstante;
  Serial.println(Temp);
}

void loop() {
  // put your main code here, to run repeatedly:
  TempMeasure();
  Serial.println(i2c_Data[0]);
}


