#include <unistd.h>     //System interaction, probably
#include <sys/types.h>  //introduces more data types (probabl derived ones which make things easier)
#include <sys/socket.h> //socket library accept...
#include <netinet/in.h> //structs for sockets
#include <string.h>
#include <thread>
#include <vector>
#include <iostream>
#include "../User/User.h"
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
			clientThreads.push_back(std::thread(&Server::ServerPrivateThread,this));//wenn nix error neu Client thread
		}
		count++;
	}
}

void Server::ServerPrivateThread()
{
	std::cout << "nope" << '\n';
}

Server::~Server()
{
	close(sockfd);
}
