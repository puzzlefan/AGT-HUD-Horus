#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "DaTa/DaTa.h"
#include "I2C.h"

int main()
{
  wiringPiSetup();

  DaTa *DATA = new DaTa();
  I2C * i2c = new I2C(DATA);
  std::cout << "Buttons:" << '\n';
  while(true)
  {
    std::cout <<"\r";
    for (int i = 0; i < 6; i++) {
      std::cout /*<<" Button: " << i << " State: " */<< DATA->getButton(i);
    }
    std::cout << std::flush;
    usleep(500000);
  }
  return 0 ;
}
