//ALU oder Plastik, das ist hier die Frage
	#define ALU

//Bluetooth zeug
	//code
		#include "Bluetooth.h"
		#include "MPU6050.h"

	//defines
		#define STATE_PIN -1 //defines if the connection has to be confirmed, in this case only in the HQ
		#define ERROR_PIN 13 //Build in LED has to be used for something fun
		#ifdev ALU
			#define VALUE_COUNT 2//number of values to be exchanged
		#endif
		#ifndev
			#define VALUE_COUNT 1//number of values to be exchanged
		#endif

	//variables
		int ToRead[VALUE_COUNT], ToWrite[VALUE_COUNT];//providing arrays
		Bluetooth *Slave;//pointer to BT-class

//Pin numbering
	#ifdev ALU
		bool alu = true;//when true the pin numbering for the aluminium version is used
	#endif
	#ifndev ALU
		bool alu = false;//when true the pin numbering for the aluminium version is used
	#endif


	int buttonUp, buttonDown, buttonRight, buttonLeft,buttonBack, buttonCertify; // declaring pin Variable names initialization happens later
	//inapropriate use of capital letters - used to encode bools as ürime factors
		const int FACTOR_UP       = 02;
		const int FACTOR_DOWN     = 03;
		const int FACTOR_RIGHT    = 05;
		const int FACTOR_LEFT     = 07;
		const int FACTOR_BACK     = 11;
		const int FACTOR_CERTIFY  = 13;

void setup()
{
  Serial.begin(9600);

  #ifdev ALU
	MPU6050_setup();
  #endif

  if(alu)//assigning the actual numbers
  {
	buttonUp		= 49;
	buttonDown		= 53;
	buttonRight		= 50;
	buttonLeft		= 52;
	buttonBack		= 51;
	buttonCertify	= 48;
  }
  else
  {
  	buttonUp		= 53;
	buttonDown		= 50;
	buttonRight		= 48;
	buttonLeft		= 51;
	buttonBack		= 52;
	buttonCertify	= 49;	 
  }
  
  //setting up the pins
  pinMode(buttonUp,INPUT);
  pinMode(buttonDown,INPUT);
  pinMode(buttonRight,INPUT);
  pinMode(buttonLeft,INPUT);
  pinMode(buttonBack,INPUT);
  pinMode(buttonCertify,INPUT);

  //Kabel-Debug
  //Slave = new Bluetooth(false, ERROR_PIN, STATE_PIN, SERIAL_THREE, VALUE_COUNT);

  //BT both versions have the same configuration
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
  Slave->setWrite(1, MPU6050_loop_very_activ());
  Slave->update();
  //Serial.println(transmit);//debug out
  delay(25);//the transmission gets f***** up when things happen to fast
 }
