 //Example for pinNo. later from PinNo-class
int buttonUp = 22;
int buttonDown = 23;
int buttonRight = 24;
int buttonLeft = 25;
int buttonBack = 28;
int buttonCertify = 27;

void setup() 
{
  //Serial.begin(9600);
  
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

/*Ausgabe
  Serial.print("UP ");
  Serial.println(Up);

  Serial.print("DOWN ");
  Serial.println(Down);
  
  Serial.print("RIGHT ");
  Serial.println(Right);

  Serial.print("LEFT ");
  Serial.println(Left);

  Serial.print("BACK ");
  Serial.println(Back);

  Serial.print("CERTIFY ");
  Serial.println(Certify);

  delay(5000);
  */
 }
