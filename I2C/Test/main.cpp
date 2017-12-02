#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main (void)
{
  wiringPiSetup();
  int fd = wiringPiI2CSetup(0x42);
  int out = 0;
  int port = 0;
  while(true)
  {
    std::cout<<"Reading: "<<wiringPiI2CReadReg16(fd, port)<<std::endl;
    std::cin >> out;
    wiringPiI2CWriteReg16 (fd,port, out) ;
  }
  return 0 ;
}
