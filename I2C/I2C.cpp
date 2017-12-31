#include "I2C.h"
#include <iostream>

I2C::I2C(DaTa* DaTaToGo, HeadGUI* NotSoInsaneUSer)
{
    MyLittleData = DaTaToGo;//store copy of Pointer to DaTa
    //InsaneUser = NotSoInsaneUSer;
    fd = wiringPiI2CSetup(ADDR); //establishes connection to Arduino
    SinkThread = new std::thread(&I2C::ReadLoop,this);//starts the thread with acces to this class
}
I2C::~I2C()
{

}

void I2C::ReadLoop()
{
    while(true)
    {
        for (int i = 0; i < DaTa::DaTaAmount; i++) // loop to read all Data
        {
            int temp = wiringPiI2CReadReg16(fd, i); //read data and store in Buffer
            if(temp < 0) break;//error collection
            if(i==KNOBS && MyLittleData->getRawDaTa(i)!=temp)//emits signal to UI when a Button was pressed
            {
                MyLittleData->setDaTa(temp,i);//refreshes stored value
                InsaneUser->newDataFromArduino();//emit the signal
            }
            else
            {
              MyLittleData->setDaTa(temp,i);//refreshes stored value
            }
            std::cout<<MyLittleData->getRawDaTa(0)<<std::endl;
            usleep(20000);
        }
        if(MyLittleData->WriteOrDontWrite())//if there is new DaTa the write registers get written
        {
            for (int i = 0; i < DaTa::FarewellAmount; i++)//loop to write all DaTa
            {
                wiringPiI2CWriteReg16(fd, DaTa::DaTaAmount - 1 + i , MyLittleData->getWriteDaTa(i));//actual write command
            }
        }
    }
}
