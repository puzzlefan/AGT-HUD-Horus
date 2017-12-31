#ifndef DATA_HEAD
#define DATA_HEAD

#include <mutex>

//Defines to make reading of Data from int Array more understandavle
#define KNOBS               0
#define TEMPRETURE_OBOVE    1
#define TEMPRETURE_BELOW    2
#define CO_TOP              3
#define CO_FLOP             4

//Defines to make reading from knobs array easier
#define KNOB_UP         0
#define KNOB_DOWN       1
#define KNOB_RIGHT      2
#define KNOB_LEFT       3
#define KNOB_BACK       4
#define KNOB_CERTIFY    5

//Primfactors to calcuate the bools back
#define KNOB_UP_PRIM         2
#define KNOB_DOWN_PRIM       3
#define KNOB_RIGHT_PRIM      5
#define KNOB_LEFT_PRIM       7
#define KNOB_BACK_PRIM       11
#define KNOB_CERTIFY_PRIM    13

class DaTa
{
public:
    static const int DaTaAmount = 5; //amount of values which get read from the I2C BUS
    static const int FarewellAmount = 1;//amount of stuff to send
    static const int ButtonAmount = 6;//amount of buttons

    DaTa();//Constructer
    ~DaTa();//Deconstructor

    int getRawDaTa(int pos);//returns actual RawData
    int getWriteDaTa(int pos);//retunrs the Data to write
    bool getButton(int pos);//returns decoded Button
    bool WriteOrDontWrite();//returns if there is unsend Data

    void setDaTa(int val, int pos);//gets RawDaTa from I2C thread
    void setSendData(int val, int pos);//gets the Data to send
private:
    //Array to calculate the bools for the buttons back
    int Primfactors[ButtonAmount] = {KNOB_UP_PRIM, KNOB_DOWN_PRIM, KNOB_RIGHT_PRIM, KNOB_LEFT_PRIM, KNOB_BACK_PRIM, KNOB_CERTIFY_PRIM};


    int RawDaTa[DaTaAmount]; //the raw stuff
    bool Buttons[ButtonAmount]; //processesd Buttons

    int Farewell[FarewellAmount];//DaTa to send

    bool SomeonePushedThatButton = false;//Stores if button state has chnaged unrecocnised
    bool SomeoneToSayGodbyTo = false; //Stores if there is Data to be send

    void boolise();//function to calc prim product back to bool

    std::mutex DaTaa;//mutex for secure multithreading 
};


#endif
