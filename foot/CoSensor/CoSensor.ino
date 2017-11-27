#include <TFT.h>

double ppm = 0;
//double ppmKonstante = 0.48828125; what teh future may bring

int i2c_Data[2];
/*
 * Index table
 * 0 == Temp
 */
int ppmOut = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void ppmMeasure(){
  ppm = analogRead(14);
  //ppm = ppm * ppmKonstante *100;maybe in the future
  i2c_Data[ppmOut] = int(ppm);
}

void debug_out(){
  ppm = analogRead(0);
  Serial.println(ppm);
}

void loop() {
  // put your main code here, to run repeatedly:
  //ppmMeasure();
  debug_out();
}
