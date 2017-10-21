#include <pinNo.h>

 //Example for pinNo. later from PinNo-class
int buttonUp = 1;
int buttonDown = 2;
int buttonRight = 3;
int buttonLeft = 4;
int buttonBack = 5;
int buttonCertify = 6;

void setup() 
{
  pinMode(buttonUp,INPUT);
  pinMode(buttonDown,INPUT);
  pinMode(buttonRight,INPUT);
  pinMode(buttonLeft,INPUT);
  pinMode(buttonBack,INPUT);
  pinMode(buttonCertify,INPUT);
}

void loop() 
{
  int Up = digitalRead(buttonUp);
  int Down = digitalRead(buttonDown);
  int Right = digitalRead(buttonRight);
  int Left = digitalRead(buttonLeft);
  int Back = digitalRead(buttonBack);
  int Certify = digitalRead(buttonCertify);
  }
