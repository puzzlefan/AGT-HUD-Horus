#ifndef I2C_HEAD
#define I2C_HEAD

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <thread>
#include "../personalGUI/headgui.h"
#include "DaTa/DaTa.h"

class I2C
{
private:
    const int ADDR = 0x42;//Adres of Arduino
    int RawDaTa[DaTa::DaTaAmount];//data to be read

    int fd; //connection token

    //DaTa
    DaTa *MyLittleData;

    //threads
	std::thread *SinkThread;

    //class to interrupt on Button
    HeadGUI *InsaneUser;
public:
    I2C(DaTa* DaTaToGo, HeadGUI* NotSoInsaneUSer);
    ~I2C();

    void ReadLoop();//thread function may need a delay to let Arduino work
    void I2C16Write(int token, int Register, int Wert);
    int I2C16Read(int token, int Register);

};

#endif
