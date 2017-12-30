#ifndef I2C_HEAD
#define I2C_HEAD

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include <unistd.h>
#include "../personalGUI/headgui.h"
#include "DaTa/DaTa.h"

class I2C
{
private:
    const int ADDR = 0x42;//Adres of Arduino
    int RawDaTa[DaTa::DaTaAmount];//data to be read
    int FarewellDaTa[DaTa::FarewellAmount];//data to send

    int fd; //connection token

    //DaTa
    DaTa *MyLittleData;

    //threads
	   std::thread *SinkThread;

    //class to interrupt on Button
    HeadGUI *InsaneUser;
public:
    I2C(DaTa* DaTaToGo, HeadGUI* NotSoInsaneUSer);//Constructer starts thread
    ~I2C();//Destructor

    void ReadLoop();//thread function that polls the Arduino with 50 Hz
};

#endif
