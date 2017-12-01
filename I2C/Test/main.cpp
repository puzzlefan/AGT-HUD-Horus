#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main (void)
{
  wiringPiSetup();
  int fd = wiringPiI2CSetup(0x42);
  int out = 0;
  while(true)
  {
    std::cout<<wiringPiI2CReadReg16(fd, 0)<<std::endl;
    std::cin >> out;
    wiringPiI2CWriteReg16 (fd,0, out) ;
  }
  return 0 ;
}
