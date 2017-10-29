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
#include "client.h"

Client::Client()
{
  sockfd = socket(AF_INET, SOCK_STREAM, 0);//open client socket end check if it worked
  if (sockfd<0) {
    std::cout << "error opening socket" << '\n';
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));//making endpoint socket identifaier ready
  serv_addr.sin_family = AF_INET;//ist im internet
  inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));//IP Adresse da wir Rasoberry Pi als Router verwenden ist diese Fix bei solange nur eine Testmaschine 127.0.0.1
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
        std::cout<<"ERROR connecting"<<"\n";
  }

  ClientThread = new std::thread(&Client::communicator,this);
}

Client::~Client()
{
  close(sockfd);
}

void Client::communicator()
{
  std::cout << "here we go" << '\n';
}

void Client::communicationWithTheCommunicator()
{

}
