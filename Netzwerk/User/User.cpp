#include "User.h"
//
//  Construct and Destruct
//

user::user()
{
  fill();
}
user::user(const user&)
{
  user();
}
user::~user()
{

}

//
//  Test functions
//

void user::fill()
{
  for(int i = 0; i < integerCount;i++)
  {
     setInteger(i, 0);
  }
  for(int i = 0; i < boolCount;i++)
  {
    setBools(i,0);//i%2;
  }
  message = "";
  for (int i = 0; i < BITBildSize; i++)
  {
	  BITBild[i] = 0;
  }
}

//
// getter to be used to get data for external programm parts
//

int user::getID()
{
  std::lock_guard<std::mutex> lock(mutex_ID);
  return id;
}
bool user::getIDChanged()
{
  std::lock_guard<std::mutex> lock(mutex_ID);
  return idChanged;
}

int user::getInt(int pos)
{
  std::lock_guard<std::mutex> lock(mutex_Integer);
  return integers[pos];
}
bool user::getIntegersChanged(int Pos)
{
  std::lock_guard<std::mutex> lock(mutex_Integer);
  return ChangedInts[Pos];
}
int user::getIntegerCount()
{
  return integerCount;
}

bool user::getBool(int pos)
{
  std::lock_guard<std::mutex> lock(mutex_Bools);
  return bools[pos];
}
bool user::getBoolChanged(int Pos)
{
  std::lock_guard<std::mutex> lock(mutex_Bools);
  return ChangedBools[Pos];
}
int user::getBoolCount()
{
  return boolCount;
}

std::string user::getMessage()
{
  std::lock_guard<std::mutex> lock(mutex_Message);
  return message;
}
bool user::getMessageChanged()
{
  std::lock_guard<std::mutex> lock(mutex_Message);
  return MessageChanged;
}
int user::getMessageLength()
{
  std::lock_guard<std::mutex> lock(mutex_Message);
  return message.size();
}

//
//  Setter to be used if you want to get Data into the Network
//

void user::setID(int DI)
{
  std::lock_guard<std::mutex> lock(mutex_ID);
  id = DI;
  idChanged = true;
}
void user::setInteger(int Pos, int Integer)
{
  std::lock_guard<std::mutex> lock(mutex_Integer);
  integers[Pos]=Integer;
  ChangedInts[Pos]=true;
}
void user::setBools(int Pos, bool Bools)
{
  std::lock_guard<std::mutex> lock(mutex_Bools);
  bools[Pos]=Bools;
  ChangedBools[Pos]=true;
}
void user::setMessage(std::string Message)
{
  std::lock_guard<std::mutex> lock(mutex_Message);
  message = Message;
  MessageChanged = true;
}

//
//  transmits, used to send the data to anther device
//

int user::transmitID()
{
  std::lock_guard<std::mutex> lock(mutex_ID);
  idChanged = false;
  return id;
}
int user::transmitInt(int pos)
{
  std::lock_guard<std::mutex> lock(mutex_Integer);
  ChangedInts[pos]=false;
  return integers[pos];
}
bool user::transmitBool(int pos)
{
  std::lock_guard<std::mutex> lock(mutex_Bools);
  ChangedBools[pos] = false;
  return bools[pos];
}
std::string user::transmitMessage()
{
  std::lock_guard<std::mutex> lock(mutex_Message);
  MessageChanged=false;
  return message;
}

//
//recieves store data which was obtained from the Network
//

void user::recieveID(int identification)
{
  std::lock_guard<std::mutex> lock(mutex_ID);
  id = identification;
}
void user::recieveInt(int Inti, int pos)
{
  std::lock_guard<std::mutex> lock(mutex_Integer);
  //ChangedInts[pos]=false;
  integers[pos]=Inti;
}
void user::recieveBool(bool Booli, int pos)
{
  std::lock_guard<std::mutex> lock(mutex_ID);
  //ChangedBools[pos]=false;
  bools[pos]=Booli;
}
void user::recieveMessage(std::string Message)
{
  std::lock_guard<std::mutex> lock(mutex_Message);
  message.clear();
  message.append(Message);
}

//
//	BIT bild is not transfered with normal function structure to improve performance by large enough amounts to justify  
//

unsigned char* user::getBITBildArray()//returns startingpoint of the picture array 
{
	//kein Mutex wird von Hand gesetzt um prozess zu beschleunigen
	return &(BITBild[0]);
}
void user::setBITBildMutex(bool PowerOnOff)//aktivieren oder deaktiviren des Mutex(wenn funktioniert wenn von aderen threads aufgerufen)
{
	if (PowerOnOff)
	{
		mutex_BitBild.lock();
	}
	else
	{
		mutex_BitBild.unlock();
	}
}
int user::getBITBildSize()//returns the length of the Bit Bildarray
{
	return BITBildSize;
}