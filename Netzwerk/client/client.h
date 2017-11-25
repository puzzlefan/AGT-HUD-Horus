#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>      //(C) STanaDart Input Output library (still works in ++) used for interaction with filesytem, keybord ... via stzreams which are associatet with pointers in the filesystem
#include <stdlib.h>     //Standart Bibliothek
#include <unistd.h>     //System interaction, probably
#include <string.h>     //handling of strings and Arrays
#include <sys/types.h>  //introduces more data types (probabl derived ones which make things easier)
#include <sys/socket.h> //socket library accept...
#include <netinet/in.h> //structs for sockets
#include <arpa/inet.h>  //provides function to convert IP to human redable and back
#include <string>
#include <iostream>
#include <thread>
#include "../User/User.h"
#include <sys/time.h>//macht zeit
#include <sys/select.h>
#include "../../personalGUI/headgui.h"
#include <QApplication>


class Client
{
private://the ip adress of the server stands in the cpp fron the client because if it stands around the other variables it wont compile
  size_t CommandLength = 1;

  int sockfd;
  uint16_t portno = 42000;
  struct sockaddr_in serv_addr;
  std::thread *ClientThread;

  user *mine;

  HeadGUI *InsaneUser;
public:
  Client(user *point, HeadGUI *NotSoInsaneUSer);
  ~Client();

  void communicator();
  void communicationWithTheCommunicator();

  void rwteble(bool *ari);
  void IntChar(int Inte, char *ptr);
};

#endif
