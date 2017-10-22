 //Example for pinNo. later from PinNo-class
int buttonUp = 78;
int buttonDown = 77;
int buttonRight = 76;
int buttonLeft = 75;
int buttonBack = 74;
int buttonCertify = 73;

void setup() 
{
  Serial.begin(9600);
  
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

  Serial.print("UP ");
  Serial.println(Up);

  Serial.print("DOWN ");
  Serial.println(Down);
  
  Serial.print("RIGHT ");
  Serial.println(Right);

  Serial.print("LEFT ");
  Serial.println(Left);

  Serial.print("DOWN ");
  Serial.println(Down);

  Serial.print("CERTIFY ");
  Serial.println(Certify);

  delay(1000);
 }
