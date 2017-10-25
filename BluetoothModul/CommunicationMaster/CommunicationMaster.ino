#include "Values.h"

#define STATE_PIN 0
#define EN_PIN 2
#define ERROR_PIN 13

//Running variables
int counter = 0;
String ToWrite ="";

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
  Serial1.write(TestConnection);
  while (!Serial1.available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      Serial.println("Still waiting for answer struggles with connection ");
      Serial.println("Resending teset");
      Serial1.write(TestConnection);
    }
    counter++;
  }
  //Serial.println(Serial1.read());
  if(Serial1.read()!=TestConnection)
  {
    digitalWrite(ERROR_PIN,HIGH);
    Serial.println("Test failed");
  }
  Serial.println("Starting loop");
}

void loop() {
  ToWrite+=something();
  ToWrite+=";";
  Serial1.println(ToWrite);
  ToWrite="";
  delay(100);
}

int something()//getting some data to send
{
  analogRead(0);
}
