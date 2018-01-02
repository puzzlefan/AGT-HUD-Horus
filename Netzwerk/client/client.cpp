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
#include "client.h"

Client::Client(user *point /*, HeadGUI *PointerHeadGUI*/)
{
  mine = point;
//  GUI = PointerHeadGUI;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);//open client socket end check if it worked
  if (sockfd<0) {
    std::cout << "error opening socket" << '\n';
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));//making endpoint socket identifaier ready
  serv_addr.sin_family = AF_INET;//ist im internet
  inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));//IP Adresse da wir Rasoberry Pi als Router verwenden ist diese Fix bei solange nur eine Testmaschine 127.0.0.1 converts human redable to computer readable and stores in socket
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
        std::cout<<"ERROR connecting Netzwerk client"<<"\n";
        return;
  }

  //timeout on connection
  WaitingTime.tv_sec = 1;//seconds
  WaitingTime.tv_usec = 0;//microsecond (10^-6)
  //ensures that a loss of connection does not quit the programm but also dont tells anybody about that
  std::signal(SIGPIPE, SIG_IGN);

  ClientThread = new std::thread(&Client::communicator,this);
}

Client::~Client()
{
  close(sockfd);
}

void Client::communicator()
{
  bool id_confirmed = false;
  char command = 0;
  //bool ReadWrite[] = {false, false};//for later use
  int fall = 0;
  //rwteble(ReadWrite);//for later use
  char abc[1];
  while(true) write(sockfd,abc,1);
  std::cout << "/* message */" << '\n';
  while (1!=2)
  {
    switch (fall) {
      case 0:   if(id_confirmed || mine->getBool(NEW_CONFIRMED_ID))
                {
                  fall = 1;//activates first order
                }
                else
                {
                  fall = 0;
                }
                break;
      case 1:   command = 001;
                write(sockfd, &command, CommandLength);//send to sockfd command 1 with length 1
                fall = 100;
                break;

      case 2:   command = 002;
                write(sockfd, &command, CommandLength);//send to sockfd command 2 with length 1
                char Position;
                char Bool;
                char Char;
                char Integer[4];
                int RecivingLength;
                do
                {
                    s_read(sockfd, &command, CommandLength);
                    switch (command) {
                    default : //std::cout << "something went horrible wrong through out reading" << '\n';
                                break;
                    case 3:     break;
                    case 200:   do
                                {
                                    s_read(sockfd, &Position, 1);
                                    if(Position == 253)
                                    {
                                        break;
                                    }
                                    s_read(sockfd, Integer, 4);
                                    mine->recieveInt((Integer[0] << 24)+(Integer[1] << 16)+(Integer[2] << 8)+Integer[3],Position);
                                } while(true);
                                break;
                    case 201:   do
                                {
                                    s_read(sockfd, &Position, 1);
                                    if(Position == 253)
                                    {
                                        break;
                                    }
                                    s_read(sockfd, &Bool, 1);
                                    mine->recieveBool(Bool,Position);
                                } while(true);
                                break;
                    case 202:   mine->recieveMessage("");
                                char MLength[4] = {0,0,0,0};
                                s_read(sockfd,MLength,4);
                                RecivingLength = (MLength[0] << 24)+(MLength[1] << 16)+(MLength[2] << 8)+MLength[3];
                                char MessagE [RecivingLength];
                                //for (int i = 0; i < mine->getMessageLength(); i++)
                                //{
                                s_read(sockfd,MessagE,RecivingLength);
                                std::string mESSAGe(MessagE,RecivingLength);
                                mine->recieveMessage(mESSAGe);
                                //}
                                break;

                  }
                } while(command!=003);
                fall = 001;
                //GUI->newDataFromHeadquater();
                break;

      case 3:   command = 003;
                write(sockfd, &command, CommandLength);//send to sockfd command 3 with length 1
                fall = 002;
                break;

      case 100: command = 100;
                write(sockfd, &command, CommandLength);//send to sockfd command 100 with length 1
                char charID[4];
                IntChar(mine->getID(),charID);
                write(sockfd, charID, 4);
                fall = 101;
                break;

      case 101: command = 101;
                write(sockfd, &command, CommandLength);//send to sockfd command 101 with length 1
                char chaInt[4];
                for (char i = 0; i < mine->getIntegerCount() ; i++)
                {
                  if (mine->getIntegersChanged(i)) {
                    write(sockfd,&i,1);
                    IntChar(mine->transmitInt(i), chaInt);
                    write(sockfd, chaInt, 4);
                  }
                }
                command = 253;
                write(sockfd,&command,1);
                fall = 102;
                break;

      case 102: command = 102;
                write(sockfd, &command, CommandLength);//send to sockfd command 102 with length 1
                for (char i = 0; i < mine->getBoolCount(); i++)
                {
                  if (mine->getBoolChanged(i)) {
                    write(sockfd,&i,1);
                    char asdf = mine->transmitBool(i);
                    write(sockfd, &asdf, 1);
                  }
                }
                command = 253;
                write(sockfd,&command,1);
                fall = 103;
                break;

      case 103: if(mine->getMessageChanged())
                {
                    command = 103;
                    write(sockfd, &command, CommandLength);//send to sockfd command 103 with length 1
                    //sent itnt for length
                    char charMessageLength[4];
                    IntChar(mine->getMessageLength()+1,charMessageLength);
                    write(sockfd, charMessageLength, 4);
                    //for(int i = 0; i< mine->getMessageLength();i++)
                    //{
                    write(sockfd, mine->transmitMessage().c_str(), mine->getMessageLength()+1);
                    //}
                }
                fall = 104;
                break;

      case 104: command = 104;//needs change
                write(sockfd, &command, CommandLength);//send to sockfd command 104 with length 1
                for(int i = 0; i< mine->getBITBildSize();i++)
                {
                    char ToWrite = mine->transmitBITBild(i);
                    write(sockfd, &ToWrite, 1);//send to sockfd command 104 with length 1
                }
                mine->setBools(UPDATE_IMAGE_SIGNAL,true);
                fall = 003;
                break;
                //OLD
                /*
                command = 104;//needs change
                char nUMMBER[4];
                write(sockfd, &command, CommandLength);//send to sockfd command 104 with length 1
                for(int i = 0; i< mine->getBITBildSize();i++)
                {
                  if(mine->getBITBildChanged(i))
                  {
                    IntChar(i,nUMMBER);
                    write(sockfd, &nUMMBER, 4);
                    char ToWrite = mine->transmitBITBild(i);
                    write(sockfd, &ToWrite, 1);//send to sockfd command 104 with length 1
                  }
                }
                char STOP[4];
                IntChar(0xFFFFFFFF,STOP);
                write(sockfd,STOP,4);
                fall = 003;
                break;
                */

      default:  //std::cout << "something wemt horrebly wrong" << '\n';
                break;
    }
  }
}


bool Client::readable()
{
  FD_ZERO(&rfds);//clear all FDs
  FD_SET(0, &rfds);//because of reasons we add fd 0
  FD_SET(sockfd, &rfds);//adding the socket which we may want to read
  if (0<select(sockfd+1,&rfds, NULL, NULL, &WaitingTime)) //http://manpages.courier-mta.org/htmlman2/select.2.html watch for reading possebilety
  {
    //in theorie it should only return 1 when it is possible to read sockfd
    return true;
  }
  else
  {
    return false;
  }
}
bool Client::writable()
{
  FD_ZERO(&wfds);//clear all FDs
  FD_SET(0, &wfds);//because of reasons we add fd 0
  FD_SET(sockfd, &wfds);//adding the socket which we may want to write
  if (0<select(sockfd+1,NULL, &wfds, NULL, &WaitingTime)) //http://manpages.courier-mta.org/htmlman2/select.2.html watch for reading possebilety
  {
    //in theorie it should only return 1 when it is possible to write to sockfd
    return true;
  }
  else
  {
    return false;
  }
}

void Client::IntChar(int Inte, char *ptr)
{
  ptr[0] = Inte >> 24;
  ptr[1] = (Inte >> 16)&0x00FF;
  ptr[2] = (Inte >> 8) & 0x0000FF;
  ptr[3] = Inte & 0x000000FF;
}

int Client::s_read(int sockFD, char *buffer, int length)
{
  if(readable())
  {
    read(sockFD, buffer, length);
    return 0;
  }
  std::cout << "connection lost nothing to read" << '\n';
  return -1;
}

//static void Client::writeERROR(int code)
//{
//  //std::cout << "/* message */" << '\n';
//}

void Client::communicationWithTheCommunicator()
{

}
