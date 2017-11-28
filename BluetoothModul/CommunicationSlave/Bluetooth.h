#include <assert.h>

int endDelay = 100;

#define SERIAL_ONE    0
#define SERIAL_TWO    1
#define SERIAL_THREE  2

class Bluetooth{
private:
  //varaibles
  bool Serial0 = true;
  char TestConnection = 1;
  int AnalogTreshhold = 500;
  int ModuloWait = 100000;

  bool changed = false;//if to write commad writes
  int Port = 0;
  int ValCount;//needs to be counted in this case it reads a Analog Port on the other Arduino
  int error_pin, state_pin;
  int *writeArray,*readArray;//pointers which become array to hold in and outgoing data

  HardwareSerial SerialPort[3]={Serial1, Serial2, Serial3};

  void MasterSetup();
  void SlaveSetup();
public:
  Bluetooth(bool Master, int errorPin, int statePin, int port, int ValueCount);
  ~Bluetooth();

  void read();
  void write();

  int getRead(int pos);
  void setWrite(int pos, int val);
};

Bluetooth::Bluetooth(bool Master, int errorPin, int statePin, int port, int ValueCount)//if statePin == 0 the statePin is not used, because the electric department does not want to correct an incompensateble error
{
  error_pin = errorPin;
  state_pin=statePin;
  Port = port;
  ValCount=ValueCount;

  writeArray = calloc(sizeof(int), ValCount);
  assert(writeArray);
  readArray = calloc(sizeof(int), ValCount);
  assert(readArray);

  for (int i = 0; i < ValCount; i++) //just for safety
  {
    readArray[i]=0;
    writeArray[i]=0;
  }

  //shared init
  //variables
  int counter = 0;
  // setting up the Pins to standart connection
  pinMode(error_pin,OUTPUT);
  digitalWrite(error_pin,LOW);

  //Start Serialport 0 for Error Messages
  Serial.begin(9600);
  Serial.println("Waiting for connection");
  //wait until a connection has beend established
  if(statePin >= 0)
  {
    while(analogRead(state_pin)<AnalogTreshhold)
    {
      if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
      {
        Serial.println("Still struggles with connection");
      }
      counter++;
    }
  }
  counter = 0;
  //Start and test the connection
  Serial.println("Test the connection");
  SerialPort[Port].begin(38400);//Do not ask why but when you try to make the integer to an variable it does not work

  //unshared init
  if (Master)
  {
    MasterSetup();
  }
  else
  {
    SlaveSetup();
  }
}
Bluetooth::~Bluetooth()
{
  free(writeArray);
  writeArray = NULL;
  free(readArray);
  readArray = NULL;
}

void Bluetooth::MasterSetup(){
  //variables
  int counter = 0;

  SerialPort[Port].write(TestConnection);
  while (!SerialPort[Port].available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      if(Serial0){
        Serial.println("Still waiting for answer struggles with connection ");
        Serial.println("Resending teset");
      }
      SerialPort[Port].write(TestConnection);
    }
    counter++;
  }
  //Serial.println(SerialPort[Port].read());
  if(SerialPort[Port].read()!=TestConnection)
  {
    digitalWrite(error_pin,HIGH);
    if(Serial0) Serial.println("Test failed");
  }
  if(Serial0) Serial.println("Starting loop");
}
void Bluetooth::SlaveSetup() {
  //variables
  int counter = 0;

  while (!SerialPort[Port].available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      Serial.println("Still waiting for request struggles with connection ");
    }
    counter++;
  }
  if(SerialPort[Port].read()!=TestConnection)
  {
    digitalWrite(error_pin,HIGH);
    Serial.println("Test failed");
  }
  else
  {
    SerialPort[Port].write(TestConnection);
  }
  Serial.println("Starting loop");
}

int Bluetooth::getRead(int pos) {
  if(pos>=0&&pos<ValCount){
    return readArray[pos];
  }
}
void Bluetooth::setWrite(int pos, int val){
  if(pos>=0&&pos<ValCount){
    if(writeArray[pos]!=val)
    {
      writeArray[pos]=val;
      changed = true;
    }
  }
}

void Bluetooth::write(){
  if(changed)
  {
    String ToWrite ="";
    for (int i = 0; i < ValCount; i++) {
      ToWrite += writeArray[i];
      ToWrite +=",";
    }
    ToWrite.remove(ToWrite.length()-1);
    ToWrite+=";";
    SerialPort[Port].println(ToWrite);
    changed = false;
  }
}
void Bluetooth::read() {
    if(SerialPort[Port].available())
    {
        int counter = 0;
        String integer, ToReadSTRING = "";
        while(true)
        {
            if(SerialPort[Port].available())
            {
                char character = SerialPort[Port].read();
                ToReadSTRING+=character;
                if(character==';') break;
            }
        }

        for(int i = 0;i<ToReadSTRING.length();i++)
        {
        if(ToReadSTRING[i]==','||ToReadSTRING[i]==';')
        {
          readArray[counter]=integer.toInt();
            counter++;
            integer.remove(0);
        }
        else
        {
          integer+=ToReadSTRING[i];
        }
        if (ToReadSTRING[i]==';') break;
        }
    }
}
