#ifndef SERVER_H
#define SERVER_H

//#define SERVER_STANDALONE //constructer manuel ändern

#include <unistd.h>     //System interaction, probably
#include <sys/types.h>  //introduces more data types (probabl derived ones which make things easier)
#include <sys/socket.h> //socket library accept...
#include <netinet/in.h> //structs for sockets
#include <string.h>
#include <thread>
#include <vector>
#include <iostream>
#include "../User/User.h"
//#include <sys/time.h>//macht zeit
#include <sys/select.h>
#include "csignal"
#ifdef SERVER_STANDALONE
#include "../../headquaterGUI/headquater.h"
#endif
class headquater;

class Server
{
private:
int CommandLength = 1;

int count = 0;  //counts the attemps to get a connection
//Vars for the main thread
int sockfd;
uint16_t portno = 42000;
struct sockaddr_in serv_addr;
//Client Vector to handle multiple at the same time
std::vector<socklen_t> SocketLengths;
std::vector<struct sockaddr_in> ClientAddresses;
std::vector<int> ClientFd;
std::vector<bool> changes;
std::vector<time_t> last;

bool protocolReboot = false;
int retryCount = 0;

//threads
std::thread *ServerMain;
std::vector<std::thread> clientThreads;
std::thread *ClockThread;


std::vector<user> *mine;

  #ifdef SERVER_STANDALONE
headquater *HQ;
  #endif
public:
Server(std::vector<user> *point /*, headquater *abc*/);
~Server();

void ServerMainThread();  //{return 1;}
void ServerPrivateThread(int counti);
void MagicalwhiteSmoke(int counti);

void IntChar(int Inte, char *ptr);
int CharInt(char *ptr);

int writi(int fd,void *buf, size_t length);  //write with connection loss detection
int recie(int fd,void *buf, size_t length);  //recieve with connection loss detection
};

#endif
