#include <TFT.h>
#include <Wire.h>

// I2C stuff
//Adress
#define SLAVE_ADDRESS 0x42
//recifed command, defines which register gets returned
int I2Ccommand = 0;
//The Register witch holds the data could nearly be any size you wish but one chapter is only 8 Bit long Arduino has only 16 bits and there shut be a max of 256 Registers
unsigned int Register[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*
 * Index table
 * 0 == Temp unten
 * 1 == Temp oben
 * 2 == Co unten
 * 3 == Co oben
 * Knöpfe decoded as primes 2,3,5,7,11,13
 */
int tempin = 0;

double Temp = 0;
double TemperaturKonstante = 0.48828125;

void setup() {
  //initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication / declare interrupt functions
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  //Anables Serial Communication for debugging
  //  Serial.begin(9600);
}

void TempMeasure(){
  Temp = analogRead(0);
  Temp = Temp * TemperaturKonstante *100; //the 100 comes from the fact that i2c dooes not know about digits after this but i still want to transfer it
  Register[tempin] = int(Temp);
}

void debug_out(){
  Temp = analogRead(0);
  Temp = Temp * TemperaturKonstante;
  Serial.println(Temp);
}

void loop() {
  // put your main code here, to run repeatedly:
  TempMeasure();
  Serial.println(Register[0]);
}
