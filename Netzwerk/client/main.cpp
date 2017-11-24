#include <stdio.h>      //(C) STanaDart Input Output library (still works in ++) used for interaction with filesytem, keybord ... via stzreams which are associatet with pointers in the filesystem
#include <stdlib.h>     //Standart Bibliothek
#include <unistd.h>     //System interaction, probably
#include <string.h>     //handling of strings and Arrays
#include <sys/types.h>  //introduces more data types (probabl derived ones which make things easier)
#include <sys/socket.h> //socket library accept...
#include <netinet/in.h> //structs for sockets
#include <string>
#include <thread>
#include <iostream>
#include "../User/User.h"
#include "client.h"



int main(int argc, char const *argv[]) {
  user a;
  a.fill();
  Client kop(&a);
  a.setMessage("hey");
  a.setBools(true,0);

  int ID = 2;

  a.setID(ID);

  int recentStatus = 0;
  int Temp1 = 0;
  int Temp2 = 0;
  int CO1= 0;
  int CO2=0;

  int* xyz[] = { &recentStatus, &Temp1, &Temp2, &CO1, &CO2};

//  sleep(1000);
  a.setMessage("abcde");

  while (true)
  {
      /*
      a.setInteger(recentStatus,RECENT_STATUS);
      a.setBools(UPDATED_STATUS_SIGNAL,true);
      recentStatus ++;

      a.setInteger(RECENT_TEMP_HEAD,Temp1);
      a.setBools(UPDATED_TEMP_HEAD_SIGNAL,true);
      Temp1 += 2;

      a.setInteger(RECENT_TEMP_FOOT,Temp2);
      a.setBools(UPDATED_TEMP_FOOT_SIGNAL,true);
      Temp2 += 3;

      a.setInteger(RECENT_CO_HEAD,Temp1);
      a.setBools(UPDATED_CO_HEAD_SIGNAL,true);
      CO1 += 5;

      a.setInteger(RECENT_CO_FOOT,Temp2);
      a.setBools(UPDATED_CO_FOOT_SIGNAL,true);
      CO2 += 7;

      for (int k = 0; k < 5; k++) {
          if(*xyz[k]>255)
          {
              *xyz[k]= *xyz[k]%k;
          }
      }
      */
  }
  return 0;
}
