#include <string>
#include <vector>
#include "User.h"

user::user()
{
  BITBild = new std::vector<unsigned char>(BITBildSize);//potentially dangerous at first call
  BITBildChanged = new std::vector<bool>(BITBildSize);
  for (int i = 0; i < boolCount; i++) {
    ChangedBools[i]=0;
  }
  for(int i = 0; i < integerCount;i++)
  {
    ChangedInts[i]=0;
  }
  fill();
}
user::~user()
{

}

void user::fill()
{
  setID(2);
  for(int i = 0; i < integerCount;i++)
  {
     setInteger(i, i+3);
  }
  for(int i = 0; i < boolCount;i++)
  {
    setBools(i,1);//i%2;
  }
  message = "abc";
  for(int i = 0; i<= 19200 * 2;i++){
    (*BITBild)[i]=252;
  }
}

void user::setInteger(int Pos, int Integer)
{
  integers[Pos]=Integer;
  ChangedInts[Pos]=true;
}
void user::setBools(int Pos, bool Bools)
{
  bools[Pos]=Bools;
  ChangedBools[Pos]=true;
}
void user::setBITBild(unsigned char Char, int Pos)
{
  (*BITBild)[Pos]=Char;
  (*BITBildChanged)[Pos]=true;
}

int user::transmitInt(int pos)
{
  ChangedInts[pos]=false;
  return integers[pos];
}
bool user::transmitBool(int pos){
  ChangedBools[pos] = false;
  return bools[pos];
}
unsigned char user::transmitBITBild(int pos)
{
  (*BITBildChanged)[pos]=false;
  return (*BITBild)[pos];
}

void user::recieveInt(int Inti, int pos)
{
  ChangedInts[pos]=false;
  integers[pos]=Inti;
}
void user::recieveBool(bool Booli, int pos)
{
  ChangedBools[pos]=false;
  bools[pos]=Booli;
}
void user::recieveBITBild(unsigned char Chari, int pos)
{
  (*BITBildChanged)[pos]=false;
  (*BITBild)[pos]=Chari;
}
