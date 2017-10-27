#include <assert.h>

int endDelay = 100;

class Bluetooth{
private:
  //varaibles
  bool Serial0 = true;
  char TestConnection = 1;
  int AnalogTreshhold = 500;
  int ModuloWait = 100000;

  bool changed = false;//if to write commad writes
  int ValCount;//needs to be counted in this case it reads a Analog Port on the other Arduino
  int error_pin, en_pin , state_pin;
  int *writeArray,*readArray;//pointers which become array to hold in and outgoing data

  void MasterSetup();
  void SlaveSetup();
public:
  Bluetooth(bool Master, int errorPin, int enPin, int statePin, int ValueCount);
  ~Bluetooth();

  void read();
  void write();

  int getRead(int pos);
  void setWrite(int pos, int val);
};

Bluetooth::Bluetooth(bool Master, int errorPin, int enPin, int statePin, int ValueCount){
  error_pin = errorPin;
  en_pin = enPin;
  state_pin=statePin;
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
  pinMode(en_pin,OUTPUT);
  pinMode(error_pin,OUTPUT);

  digitalWrite(en_pin,LOW);
  digitalWrite(error_pin,LOW);

  //Start Serialport 0 for Error Messages
  Serial.begin(9600);
  Serial.println("Waiting for connection");
  //wait until a connection has beend established
  while(analogRead(state_pin)<AnalogTreshhold)
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
Bluetooth::~Bluetooth(){
  free(writeArray);
  writeArray = NULL;
  free(readArray);
  readArray = NULL;
}

void Bluetooth::MasterSetup(){
  //variables
  int counter = 0;

  Serial1.write(TestConnection);
  while (!Serial1.available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      if(Serial0){
        Serial.println("Still waiting for answer struggles with connection ");
        Serial.println("Resending teset");
      }
      Serial1.write(TestConnection);
    }
    counter++;
  }
  //Serial.println(Serial1.read());
  if(Serial1.read()!=TestConnection)
  {
    digitalWrite(error_pin,HIGH);
    if(Serial0) Serial.println("Test failed");
  }
  if(Serial0) Serial.println("Starting loop");
}
void Bluetooth::SlaveSetup() {
  //variables
  int counter = 0;

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
    digitalWrite(error_pin,HIGH);
    Serial.println("Test failed");
  }
  else
  {
    Serial1.write(TestConnection);
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
    Serial1.println(ToWrite);
    changed = false;
  }
}
void Bluetooth::read() {
    if(Serial1.available())
    {
        int counter = 0;
        String integer, ToReadSTRING = "";
        while(true)
        {
            if(Serial1.available())
            {
                char character = Serial1.read();
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
