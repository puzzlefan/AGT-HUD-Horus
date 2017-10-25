#define STATE_PIN 0
#define EN_PIN 2
#define ERROR_PIN 13

//varaibles
char TestConnection = 1;
int AnalogTreshhold = 500;
int counter = 0;
int SerialSpeed = 38400;
int ModuloWait = 100000;
const int MessageLength = 100;//needs to be one bigger than it is to be NUll Terminated
const int ValueCount = 3;

char ToRead[MessageLength];//could go very wrong
int data[ValueCount];

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
  bool inLine = true;
  while(inLine)
  {
    if(Serial1.available())
    {
      char character = Serial1.read();
      ToRead[counter]=character;
      counter++;
      if(character==';'||counter-1 == MessageLength) inLine = false;
    }
  }
  inLine = true;
  String integer;
  counter = 0;
  for(int i = 0;i<MessageLength;i++)
  {
    if (ToRead[i]==';') break;
    if(ToRead[i]!=',')
    {
      integer+=ToRead[i];
    }
    else{
      data[counter]=integer.toInt();
      counter++;
      integer.remove(0);
    }
  }

  // atoi(ToRead);
  Serial.print(data[0]);
  Serial.print(" ");
  Serial.print(data[1]);
  Serial.print(" ");
  Serial.print(data[2]);
  Serial.println();
  counter = 0;
}
