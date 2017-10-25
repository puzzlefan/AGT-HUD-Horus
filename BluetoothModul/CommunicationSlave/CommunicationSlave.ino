#include "Values.h"

#define STATE_PIN 0   //depends on device
#define EN_PIN 2      //depends on device
#define ERROR_PIN 13  //depends on device

//varaibles
int counter = 0;

String ToRead = "";//char ToRead[MessageLength+1];//needs to be one bigger than it is to be NUll Terminated
int data[ValueCount];//is going to be replaced later by I²C array

void setup() {
  // setting up the Pins to standart connection
  pinMode(EN_PIN,OUTPUT);
  pinMode(ERROR_PIN,OUTPUT);

  digitalWrite(EN_PIN,LOW);
  digitalWrite(ERROR_PIN,LOW);

  //Start Serialport 0 for Error Messages
  Serial.begin(9600);
  Serial.println("Waiting for connection");
  //wait until a connection has beend established
  while(analogRead(STATE_PIN)<AnalogTreshhold)
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      Serial.println("Still struggles with connection");
    }
    counter++;
  }
  counter = 0;
  //Start and test the connection
  Serial.println("Test the connection");
  Serial1.begin(38400);//Do not ask why but when you try to make the integer to an variable it does not work
  while (!Serial1.available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      Serial.println("Still waiting for request struggles with connection ");
    }
    counter++;
  }
  if(Serial1.read()!=TestConnection)
  {
    digitalWrite(ERROR_PIN,HIGH);
    Serial.println("Test failed");
  }
  else
  {
    Serial1.write(TestConnection);
  }
  Serial.println("Starting loop");
  counter = 0;
}

void loop() {
  while(true)
  {
    if(Serial1.available())
    {
      char character = Serial1.read();
      ToRead+=character;
      if(character==';') break;
    }
  }
  String integer;
  for(int i = 0;i<ToRead.length();i++)
  {
    if(ToRead[i]==','||ToRead[i]==';')
    {
      data[counter]=integer.toInt();
      counter++;
      integer.remove(0);
    }
    else
    {
      integer+=ToRead[i];
    }
    if (ToRead[i]==';') break;
  }
  counter = 0;
  something();
}

void something()//does something with the Data which has been archived
{
  Serial.println(data[0]);
}
