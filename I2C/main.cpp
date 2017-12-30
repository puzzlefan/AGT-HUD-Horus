#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "DaTa/DaTa.h"
//#include "Serial.h"
#include "I2C.h"

int main()
{
  wiringPiSetup();

  DaTa *DATA = new DaTa();
  I2C *i2c = new I2C(DATA);
  //Serial *SERIAL = new Serial(DATA);
  std::cout << "Buttons:" << '\n';
  while(true)
  {
    std::cout <<"\r";
    for (int i = 0; i < 6; i++) {
      std::cout /*<<" Button: " << i << " State: " */<< DATA->getButton(i);
    }
    std::cout << "Temp Fuß= " << DATA->getRawDaTa(1);
    std::cout << "Temp PPM= " << DATA->getRawDaTa(3);
    std::cout << std::flush;
    //  std::cout /*<<" Button: " << i << " State: " */<< DATA->getRawDaTa(2)<<std::flush;
    //usleep(500000);
  }
  return 0 ;
}
