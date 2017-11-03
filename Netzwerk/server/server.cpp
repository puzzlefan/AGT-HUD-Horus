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
#include "server.h"

using namespace std;
Server::Server()
{
	sockfd = socket(AF_INET, SOCK_STREAM,0);//Creates a standart Socket ready for TCP
	if (sockfd<0)//validiti check
	{
		cout << "Socket Adresse ungültig" << '\n';
	}
	bzero((char *)&serv_addr, sizeof(serv_addr));//clearing the address for safety

	serv_addr.sin_family = AF_INET;//tells the socket to use the IP protocoll in this case it should be Version 4
	serv_addr.sin_addr.s_addr = INADDR_ANY;//tells the socket it's IP-Address in our case we just use that one we already have
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr))<0) {//das betriebssysterm mit unserem Socket bekanntmachen, so dass es zu uns leiten kann
		std::cout << "error on binding" << '\n';
	}

	listen(sockfd,5);; //tells the system to listen for incoming requests and que them for us to a max length of 5 because why not 5

	//
	//starting the first thread, that one only handles acception of connection because it ohterwise would block the continuation of the programm
	//
	ServerMain = new thread(&Server::ServerMainThread,this);
}

void Server::dataExchange()
{

}

void Server::ServerMainThread()
{
	while (true) {
		struct sockaddr_in HeWasNeverSeenAgain;//create socket adress to store in Vector
		ClientAddresses.push_back(HeWasNeverSeenAgain);//storing
		SocketLengths.push_back(sizeof(ClientAddresses[count]));//get the size of the stored address
		ClientFd.push_back(accept(sockfd, (struct sockaddr *) &ClientAddresses[count], &SocketLengths[count]));//taking a connection and extract it, store fd in vector
	 	if (ClientFd[count] < 0)//wenn error nix neu thread
	 	{
		 	std::cout << "ERROR on accept" << '\n';
	 	}
		else{
			clientThreads.push_back(std::thread(&Server::ServerPrivateThread,this,count));//wenn nix error neu Client thread
		}//pass by value?
		count++;
	}
}

void Server::ServerPrivateThread(int counti)
{
	int fall = 0;
	int command = 0;
	int Position;
	char Bool, Char;
	char Integer[4];
	bool Continue = true;
	while (true) {
		switch (fall) {
			case 0:	read(ClientFd[counti],&command,1);
							fall = command;
							break;
			case 1:	while (Continue)
							{
								read(sockfd,&command,1);
								switch (command) {
									case 3:	Continue = false;
													break;
									case 100:	read(ClientFd[counti],&Integer,4);
														mine.setID(CharInt(Integer));
														break;
									case 101:	do
														{
															read(ClientFd[counti], &Position, 1);
															if(Position == 253)
															{
																break;
															}
															read(sockfd, &Integer, 4);
															mine.setInteger((Integer[0] << 24)+(Integer[1] << 16)+(Integer[2] << 8)+Integer[3],Position);
														}while (true);
														break;
									case 102:do
														{
															read(sockfd, &Position, 1);
															if(Position == 253)
															{
																break;
															}
															read(sockfd, &Bool, 1);
															mine.setBools(Bool,Position);
														} while(true);
														break;
									case 103:do
														{
															read(sockfd,Integer,4);
															int Zahl = (Integer[0] << 24)+(Integer[1] << 16)+(Integer[2] << 8)+Integer[3];
															if(Zahl==0xFFFFFFFF) break;
															read(sockfd, &Char,1);
															mine.setBITBild(Char,Zahl);
														} while(true);
														break;
									case 104:
														break;
									default: std::cout << "wrong ab receving" << '\n';
								}
							}
							break;
			case 2:break;
			default: std::cout << "something went wrong" << '\n';
		}
	}
}

void Server::IntChar(int Inte, char *ptr)
{
  ptr[0] = Inte >> 24;
  ptr[1] = (Inte >> 16)&0x00FF;
  ptr[2] = (Inte >> 8) & 0x0000FF;
  ptr[3] = Inte & 0x000000FF;
}
int Server::CharInt(char *ptr)
{
	return (ptr[0] << 24)+(ptr[1] << 16)+(ptr[2] << 8)+ptr[3];
}

Server::~Server()
{
	close(sockfd);
}
