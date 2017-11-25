#ifndef USER_H
#define USER_H

//Defines für Bool Array
#define NEW_CONFIRMED_ID            0
#define UPDATED_STATUS_SIGNAL       1
#define UPDATED_TEMP_HEAD_SIGNAL    2
#define UPDATED_TEMP_FOOT_SIGNAL    3
#define UPDATED_CO_HEAD_SIGNAL      4
#define UPDATED_CO_FOOT_SIGNAL      5
#define ANSWERD_MESSAGE_SIGNAL      6
#define UPDATE_IMAGE_SIGNAL         7

//Defines  für Int Array
#define RECENT_STATUS           0
#define RECENT_TEMP_HEAD        1
#define RECENT_TEMP_FOOT        2
#define RECENT_CO_HEAD          3
#define RECENT_CO_FOOT          4
#define LEAST_SIGNIFICANT_PIXEL 5
#define MOST_SIGNIFICANT_PIXEL  6
#define NEW_MESSAGE             7
#define ANSWER                  8

#include <string>
#include <vector>

class user{
private:
  int id; //identification number
  static const int integerCount = 7;//length of integer Array
  static const int boolCount = 8/*vlient*/+1/*server*/;//Length of bool Array
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

  void setInteger(int Pos, int Integer);
  void setBools(int Pos, bool Bools);
  void setBITBild(unsigned char Char, int Pos);
  void setID(int DI){id= DI;}
  void setMessageChanged(bool no){MessageChanged = no;}

  void recieveInt(int Inti, int pos);
  void recieveBool(bool Booli, int pos);
  void recieveBITBild(unsigned char Chari, int pos);
};
#endif
