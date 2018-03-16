#include "Bluetooth.h"
#include "i2c_Arduino_as_slave_support_for_16_bit_reading_and_writing.h"

//deciding witch version of modul is used
#define ALU

#define ERROR_PIN   13 //LED could blink in case of error

#define STATE_FOOT  -1//Indication pin Foot Bluetooth has a connection
#define STATE_ARM   -1//Indication pin Arm Bluetooth has a connection

#define VALUE_COUNT_FOOT  2//amount of values from foot modul

#ifdef ALU
	#define VALUE_COUNT_ARM   2//amount of values from arm modul
#endif
#ifndef ALU
	#define VALUE_COUNT_ARM   1//amount of values from arm modul
#endif

Bluetooth *MasterFoot, *MasterArm;

#ifdef ALU
	//pins 
	int Lampe	= 44;//need to be adjusted
	int L1		= 47;//LED leiste 1 bis 3
	int L2		= 46;
	int L3		= 45;
	//wandler m�ssten funktionieren
#endif
#ifndef ALU
	int Lampe	= 13;
#endif

#ifdef ALU
	//time-for blinking
	unsigned long time = millis();
	int duration = 200;
#endif

void setup() {
  //Anables Serial Communication for debugging
  Serial.begin(9600);
  
  #ifdef ALU
	//BT
	MasterFoot = new Bluetooth(true, ERROR_PIN, STATE_FOOT, SERIAL_THREE, VALUE_COUNT_FOOT);
	delay(endDelay);//has proofen itself to work better
	//BT
	MasterArm = new Bluetooth(true, ERROR_PIN, STATE_ARM, SERIAL_TWO, VALUE_COUNT_ARM);
	//Kabel-for debug without BT
	//MasterArm = new Bluetooth(true, ERROR_PIN, STATE_ARM, SERIAL_THREE, VALUE_COUNT_ARM);
  #endif
  #ifndef ALU
	//BT
	MasterArm = new Bluetooth(true, ERROR_PIN, STATE_ARM, SERIAL_ONE, VALUE_COUNT_ARM);
  #endif
  

  //I2C
	//initialize i2c as slave
		Wire.begin(SLAVE_ADDRESS);
	//define callbacks for i2c communication / declare interrupt functions
		Wire.onReceive(receiveData);
		Wire.onRequest(sendData);
  //ensures all is set up for use of i2c
		I2CSetup();

  //Pins
  #ifdef ALU
	pinMode(Lampe,OUTPUT);
	pinMode(L1,OUTPUT);
	pinMode(L2,OUTPUT);
	pinMode(L3,OUTPUT);
	//pinMode(12,OUTPUT);//needs testing without this line

    pinMode(48,OUTPUT);
    digitalWrite(48,HIGH);
  #endif
  #ifndef ALU
	pinMode(Lampe,OUTPUT);
	//ensouring nothing bad happens when data which is not available on the plastique version is asked
	for(int i = 1;i<=4;i++) Register[i] = 42;
  #endif	
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
  #ifdef ALU
	MasterFoot->update();
  #endif
  MasterArm->update();

  Register[0] = MasterArm->getRead(0);//gets factor of button primes
  #ifdef ALU
	Register[1] = MasterFoot->getRead(1);//gets temp of foot multiplaid by 100 so we dont luse the digits after , directly
	Register[2] = analogRead(14)*0.48828125;//random(0,255);//simulates hear read out of Tempreture
	Register[3] = MasterFoot->getRead(0);//gets ppm foot
	Register[4] = analogRead(15);//random(0,255);//simulates hear read out of ppm
	Register[5] = MasterArm->getRead(1);//gets the alive bit
  #endif

  if(Register[6]==1)
  {
    digitalWrite(Lampe,HIGH);
  }
  else
  {
    digitalWrite(Lampe,LOW);
  }  

  #ifdef ALU
	//time Stuff  
  if(Register[7]==1)
  {
	  unsigned long newTime = millis();
	  if(newTime < time + duration)
	  {
		  digitalWrite(L1,HIGH);
		  digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
	  }
	  else
	  {
		  digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
		  if(newTime < time + 2 * duration)
      {
				time = millis();
		  }
	  }
  }
  else
  {
    digitalWrite(L1,LOW);
    digitalWrite(L2,LOW);
    digitalWrite(L3,LOW);
    time = millis();
  }
  #endif
  delay(endDelay);//prevents errors that occur when running to fast
}
