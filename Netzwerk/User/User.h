#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class user{
private:
  int id; //identification number
  static const int integerCount = 10;//length of integer Array
  static const int boolCount = 10;//Length of bool Array
  static const int messageLength = 140;//because why not could get dynamic
  static const int BITBildSize = 39360;//IS HARDCODED; BECAUASE OF TIME SO CHANGE IT IF THE RESOLUTION CHANGES
  int integers[integerCount];
  bool bools[boolCount];
  bool ChangedInts[integerCount];
  bool ChangedBools[boolCount];
  std::vector<unsigned char> *BITBild;
  std::vector<bool> *BITBildChanged;
  bool MessageChanged = false;
public:
  std::string message;

  user();
  ~user();

  void fill();

  int getID() {return id;}
  int getInt(int pos) {return integers[pos];}
  bool getBool(int pos) {return bools[pos];}
  int transmitInt(int pos);
  bool transmitBool(int pos);
  bool getBoolChanged(int Pos) {return ChangedBools[Pos];}
  bool getIntegersChanged(int Pos) {return ChangedInts[Pos];}
  std::string* getString() {return &message;}
  unsigned char getBITBild(int pos) {return (*BITBild)[pos];}
  unsigned char transmitBITBild(int pos);
  bool getBITBildChanged(int pos) {return (*BITBildChanged)[pos];}

  int getIntegerCount() {return integerCount;}
  int getBoolCount() {return boolCount;}
  int getMessageLength() {return messageLength;}
  int getBITBildSize() {return BITBildSize;}
  bool getMessageChanged() {return MessageChanged;}

  void setInteger(int Integer, int Pos);
  void setBools(bool Bools, int Pos);
  void setBITBild(unsigned char Char, int Pos);
  void setID(int DI){id= DI;}
  void setMessageChanged(bool no){MessageChanged = no;}

  void recieveInt(int Inti, int pos);
  void recieveBool(bool Booli, int pos);
  void recieveBITBild(unsigned char Chari, int pos);
};
#endif
