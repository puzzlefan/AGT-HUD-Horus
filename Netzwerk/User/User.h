#ifndef USER_H
#define USER_H

//Defines für Bool Array, so that they can nearly be used as normal bools
#define NEW_CONFIRMED_ID            0
#define UPDATED_STATUS_SIGNAL       1
#define UPDATED_TEMP_HEAD_SIGNAL    2
#define UPDATED_TEMP_FOOT_SIGNAL    3
#define UPDATED_CO_HEAD_SIGNAL      4
#define UPDATED_CO_FOOT_SIGNAL      5
#define ANSWERD_MESSAGE_SIGNAL      6
#define UPDATE_IMAGE_SIGNAL         7
#define NEW_MESSAGE                 8

//Defines  für Int Array so that they can nearly be used as normal integers
#define RECENT_STATUS           0
#define RECENT_TEMP_HEAD        1
#define RECENT_TEMP_FOOT        2
#define RECENT_CO_HEAD          3
#define RECENT_CO_FOOT          4
#define LEAST_SIGNIFICANT_PIXEL 5
#define MOST_SIGNIFICANT_PIXEL  6
#define ANSWER                  7

//Includes which are needet for the user Class
#include <string>
#include <vector>
#include <mutex>


class user{
private:

  //
  // constant values
  //

  static const int integerCount = 8;//length of integer Array
  static const int boolCount = 8/*von client zurück*/ + 1;//Length of bool Array
  static const int BITBildSize = 39360;//PacketWords(82 80 Pixel + 2 Header wörter)*2(Wörter sind 2 übertragende Byes) * 120(Anzahl Zeilen) * 2(zwei Segmente pro Zeile)//IS HARDCODED; BECAUASE OF TIME. SO CHANGE IT IF THE RESOLUTION CHANGES
  //static const int messageLength = 140;//because why not could get dynamic

  //
  //  transfer values
  //

  int id; //identification number
  bool idChanged = false;

  int integers[integerCount];//all intergers besides the id are sent over the array, so they dont need extra functions
  bool bools[boolCount];//all bools get send over the array because see above

  bool ChangedInts[integerCount];//ensures only values get transmittet when they have changed for integers
  bool ChangedBools[boolCount];//same as above for booles

  unsigned char BITBild[BITBildSize];//Array in which the picture is stored

  std::string message;  //message storage
  bool MessageChanged = false;//Indicates if the Message needs to get transfered

  //
  //  thread saving
  //

  std::mutex mutex_ID;    //mutex lock for ID
  //std::mutex mutex_ID_Ch; //mutex lock for id changed

  std::mutex mutex_Integer;     //mutex lock for integers
  //std::mutex mutex_Integer_Ch;  //mutex lock for integers changed

  std::mutex mutex_Bools;    //mutex lock for bools
  //std::mutex mutex_Bools_Ch; //mutex lock for bools changed

  std::mutex mutex_BitBild; //mutex lock for BitBild
  //std::mutex mutex_BitBild_Ch; //mutex lock for BitBild changed

  std::mutex mutex_Message; //mutex lock for Message
  //std::mutex mutex_Message; //mutex lock for Message changed
public:

  //
  // con and destruct
  //

  user(const user&);
  user();
  ~user();

  //
  //  testing functions
  //

  void fill(); //testing function tu run in constructor not thread safe

  //
  // getter to be used to read data into the non network parts
  //
  int getID();          //returns id leceas changed untouched
  bool getIDChanged();  //returns if the id has been changed and needs to be transmitted

  int getInt(int pos);              //returns int at given position, changed untouched
  bool getIntegersChanged(int Pos); //returns changedInts state at given position
  int getIntegerCount();            //returns length of array

  bool getBool(int pos);         //returns bool at given position, changed untouched
  bool getBoolChanged(int Pos);  //returns changedBools state at given position
  int getBoolCount();            //returns length of array

  std::string getMessage();  //returns string with message, changed untouched
  bool getMessageChanged(); //returns if message has been changed
  int getMessageLength();   //returns legth of message

  //
  // setter to be used by non network components
  //

  void setID(int DI);                            //changes ID, set changed to true
  void setInteger(int Pos, int Integer);         //sets the value of an integer at given position, changes change state to true
  void setBools(int Pos, bool Bools);            //sets the value of an bool at given position, changes change state to true
  void setMessage(std::string Message);          //changes message, sets changed message true
  

  //
  //  transmits used to send data from one computer to another
  //

  int transmitID();                       //returns ID removes changed state
  int transmitInt(int pos);               //returns int removes changed stage
  bool transmitBool(int pos);             //returns bool removes changed stage
  std::string transmitMessage();          //returns message string

  //
  //  recieves used t get the data from the network onto the machine, gets important when variables can be changed from both sides
  //

  void recieveID(int identification);                  //grabs new ID leaves changed state untouched
  void recieveInt(int Inti, int pos);                 //grabs integer for given position, leaves changed untouched
  void recieveBool(bool Booli, int pos);              //grabs bool for given position, leaves changed untouched
  void recieveMessage(std::string Message);                   //grabs message, leaves changed untouched

  //
  // Bildübertragung
  //
  void setBITBildMutex(bool PowerOnOff);	//returns array handle
  unsigned char* getBITBildArray();			//returns char at given position, changed untouched
  int getBITBildSize();						//returns length of vector
};
#endif
