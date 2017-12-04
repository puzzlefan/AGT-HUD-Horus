#include "I2C.h"

#include <iostream>

I2C::I2C(DaTa* DaTaToGo/*, HeadGUI* NotSoInsaneUSer*/)
{
    MyLittleData = DaTaToGo;
    //InsaneUser = NotSoInsaneUSer;
    fd = wiringPiI2CSetup(ADDR);
    pinMode(29,INPUT);
    SinkThread = new std::thread(&I2C::ReadLoop,this);
}
I2C::~I2C()
{

}

void I2C::ReadLoop()
{
    while(true)
    {
        for (int i = 0; i < DaTa::DaTaAmount; i++)
        {
            int temp = wiringPiI2CReadReg16(fd, i);
            if(i==KNOBS && MyLittleData->getRawDaTa(i)!=temp)
            {
                MyLittleData->setDaTa(temp,i);
                //InsaneUser->newDataFromArduino();
            }
            else
            {
              MyLittleData->setDaTa(temp,i);
            }
            usleep(20000);
        }
        if(MyLittleData->WriteOrDontWrite())
        {
            for (int i = 0; i < DaTa::FarewellAmount; i++)
            {
                wiringPiI2CWriteReg16(fd, DaTa::DaTaAmount - 1 + i , MyLittleData->getWriteDaTa(i));
            }
        }
    }
}
