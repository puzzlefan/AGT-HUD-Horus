#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class user{
private:
  int id;
  static const int integerCount = 10;
  static const int boolCount = 10;
  static const int messageLength = 140;//because why not could get dynamic
  static const int BITBildSize = 39360;//IS HARDCODED; BECAUASE OF TIME SO CHANGE IT IF THE RESOLUTION CHANGES
  int integers[integerCount];
  bool bools[boolCount];
  std::vector<unsigned char> *BITBild;
public:
  std::string message;

  user();
  ~user();

  void fill();

  int getID() {return id;}
  int getInt(int pos) {return integers[pos];}
  bool getBool(int pos) {return bools[pos];}
  std::string* getString() {return &message;}
  unsigned char getBITBild(int pos) {return (*BITBild)[pos];}

  int getIntegerCount() {return integerCount;}
  int getBoolCount() {return boolCount;}
  int getMessageLength() {return messageLength;}
  int getBITBildSize() {return BITBildSize;}

  void setInteger(int Integer, int Pos){integers[Pos]=Integer;}
  void setBools(bool Bools, int Pos){bools[Pos]=Bools;}
  void setBITBild(unsigned char Char, int Pos){(*BITBild)[Pos]=Char;}
  void setID(int DI){id= DI;}

};

#endif
