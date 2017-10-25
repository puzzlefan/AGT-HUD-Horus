#define STATE_PIN 0
#define EN_PIN 2
#define ERROR_PIN 13

//varaibles
char TestConnection = 1;
int AnalogTreshhold = 500;
int counter = 0;
int SerialSpeed = 38400;
int ModuloWait = 100000;

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
}

void loop() {
  if(Serial1.available())
  {
    Serial.println(Serial1.read());
    Serial.write(Serial1.read());
  }
}
