#include <assert.h>

int endDelay = 100;

#define SERIAL_ONE    0
#define SERIAL_TWO    1
#define SERIAL_THREE  2

//define to enable Serial Debug
#define SERIAL_DEBUG

class Bluetooth{
private:
  //varaibles
  char TestConnection = 1;//value to test if the other end of the line is the one we want to talk to
  int AnalogTreshhold = 500;//value which would be called high to detect if the BT-Modul is connected to anythyng
  int ComTreshold = 1000;//times whre the Master has not recived an answer from client (may be a litle bit low for generell use, but in our case the slave is pretty lazy)
  int ModuloWait = 100000;//a kind of delay

  bool MASTER = false;//safes if the device is the master of the communication
  bool changed = false;//if to write commad writes
  int WaitingTimeCount = 0;//counter to restart snowball game when there is no action left
  int WaitingTimeCountTwo = 0;//counter to stop waitng for serial data
  int Port = 0;//The Serial port which is used
  int ValCount;//needs to be counted in this case it reads a Analog Port on the other Arduino
  int error_pin, state_pin;//vaiables for used Pins
  int *writeArray,*readArray;//pointers which become array to hold in and outgoing data
  String ToReadSTRING = "";//input string to hold incoming data, is gloable, because if the space is not reserved early enough the programm commits suicide sometimes

  HardwareSerial* SerialPort[3]={&Serial1, &Serial2, &Serial3};//Array of available SerialPorts

  void MasterSetup();//kind of a constructer for the master side
  void SlaveSetup();//kind of a constructer for the slave side
public:
  Bluetooth(bool Master, int errorPin, int statePin, int port, int ValueCount);//constructer
  ~Bluetooth();//destructer

  void read();//read Serial input
  void write();//writes write array
  void update();//does both + ensures that only things are send which can be reseved

  int getRead(int pos);//ouputs the readings safed in the read array
  void setWrite(int pos, int val);//sets value in the write array
};

Bluetooth::Bluetooth(bool Master, int errorPin, int statePin, int port, int ValueCount)//if statePin == 0 the statePin is not used, because the electric department does not want to correct an incompensateble error
{
  error_pin = errorPin;
  state_pin=statePin;
  Port = port;
  MASTER = Master;
  ValCount=ValueCount + 1;//reserves the space for the aknowledge bit
  ToReadSTRING.reserve(6 * ValueCount + 2);//6 because a 16bit integerneeds 5 letters and one is neededd for the ,/; +2 reserves the space for the aknowledge bit and the ;

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

  #ifdef SERIAL_DEBUG
    //Start Serialport 0 for Error Messages
    if(!Serial) Serial.begin(9600);
    Serial.println("Waiting for connection");
  #endif
  //wait until a connection has beend established
  if(statePin >= 0)
  {
    while(analogRead(state_pin)<AnalogTreshhold)
    {
      if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
      {
        #ifdef SERIAL_DEBUG
          Serial.println("Still struggles with connection");
        #endif
      }
      counter++;
    }
  }
  counter = 0;
  //Start and test the connection
  #ifdef SERIAL_DEBUG
    Serial.println("Test the connection");
  #endif
  SerialPort[Port]->begin(38400);//Do not ask why but when you try to make the integer to an variable it does not work

  //unshared init
  if (Master)
  {
    changed = true;
    readArray[ValCount-1]=1;//starts the snowball game with the Master
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

  SerialPort[Port]->write(TestConnection);
  while (!SerialPort[Port]->available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      #ifdef SERIAL_DEBUG
        Serial.println("Still waiting for answer struggles with connection ");
        Serial.println("Resending teset");
      #endif
      SerialPort[Port]->write(TestConnection);
    }
    counter++;
  }
  if(SerialPort[Port]->read()!=TestConnection)
  {
    digitalWrite(error_pin,HIGH);
    #ifdef SERIAL_DEBUG
      Serial.println("Test failed");
    #endif
  }
  #ifdef SERIAL_DEBUG
    Serial.println("Starting loop");
  #endif
}
void Bluetooth::SlaveSetup() {
  //variables
  int counter = 0;

  while (!SerialPort[Port]->available())
  {
    if(counter%ModuloWait==0)//every ModuloWait times it sends a mmesage that it still struggles to connect
    {
      #ifdef SERIAL_DEBUG
        Serial.println("Still waiting for request struggles with connection ");
      #endif
    }
    counter++;
  }
  if(SerialPort[Port]->read()!=TestConnection)
  {
    digitalWrite(error_pin,HIGH);
    #ifdef SERIAL_DEBUG
      Serial.println("Test failed");
    #endif
  }
  else
  {
    SerialPort[Port]->write(TestConnection);
  }
  #ifdef SERIAL_DEBUG
    Serial.println("Starting loop");
  #endif
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
    SerialPort[Port]->print(ToWrite);
    changed = false;
    #ifdef SERIAL_DEBUG
      Serial.println(ToWrite);
    #endif
  }
}
void Bluetooth::read() {//may be need to add a real read to remove the ;
    if(SerialPort[Port]->available())
    {
      for(int i = 0; i < ValCount;i++)
      {
        readArray[i]=SerialPort[Port]->parseInt();
        #ifdef SERIAL_DEBUG
          Serial.print("Read array position: ");
          Serial.print(i);
          Serial.print(" value: ");
          Serial.println(readArray[i]);
        #endif
        if(SerialPort[Port]->peek()==';') break;
      }
    }
}
void Bluetooth::update(){
    read();
    if(getRead(ValCount-1)==1)//if the last element of the read Array is 1 the other side is ready for the next info
    {
      writeArray[ValCount-1] = 1;//ensures the last parameter is the needet 1 to keep the snowball game alive
      changed = true;//sames
      write();//actually writes the array
      readArray[ValCount-1] = 0;//ensures this part does not end in an infinite loop with itself
    }
    else
    {
        if(MASTER)
        {
          WaitingTimeCount++;
          if (WaitingTimeCount==ComTreshold)
          {
            readArray[ValCount-1] = 1;
            changed = true;
            WaitingTimeCount = 0;
            #ifdef SERIAL_DEBUG
              Serial.println("Communication timed out refused answear");
            #endif
          }
        }
    }
}
