#define STATE_PIN 0
#define EN_PIN 2
#define ERROR_PIN 13

//varaibles
char TestConnection = 1;
int AnalogTreshhold = 500;
int counter = 0;
int SerialSpeed = 38400;
int ModuloWait = 100000;
const int MessageLength = 100;

char ToRead[MessageLength];//could go very wrong

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
      char a = Serial1.read();
      Serial.print(a);//Serial1.readString());
      ToRead[counter]=a;
      counter++;
      if(a==";"||counter == 1000) break;
    }
  }
  Serial.println();
  Serial.print("Array; ");
  Serial.println(ToRead[0]+ToRead[1]+ToRead[2]);
  counter = 0;
}
