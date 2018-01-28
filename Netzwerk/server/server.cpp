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
#ifdef SERVER_STANDALONE
#include "../../headquaterGUI/headquater.h"
#endif
#include "server.h"


using namespace std;
Server::Server(std::vector<user> *point /*, headquater *abc*/)
{
								std::signal(SIGPIPE, SIG_IGN);//let write errors dont crash the programm

								mine = point;
	#ifdef SERVER_STANDALONE
								HQ = abc;
	#endif
								//SignalEmpfaenger = poinTI;
								sockfd = socket(AF_INET, SOCK_STREAM,0);//Creates a standart Socket ready for TCP
								if (sockfd<0)//validiti check
								{
																cout << "Socket Adresse ungültig" << '\n';
								}
								bzero((char *)&serv_addr, sizeof(serv_addr));//clearing the address for safety

								serv_addr.sin_family = AF_INET;//tells the socket to use the IP protocoll in this case it should be Version 4
								serv_addr.sin_addr.s_addr = INADDR_ANY;//tells the socket it's IP-Address in our case we just use that one we already have
								serv_addr.sin_port = htons(portno);

								if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) {//das betriebssysterm mit unserem Socket bekanntmachen, so dass es zu uns leiten kann
																std::cout << "error on binding" << '\n';
								}

								listen(sockfd,5);; //tells the system to listen for incoming requests and que them for us to a max length of 5 because why not 5

								//
								//starting the first thread, that one only handles acception of connection because it ohterwise would block the continuation of the programm
								//
								ServerMain = new thread(&Server::ServerMainThread,this);
}

void Server::ServerMainThread()
{
								while (true) {
																struct sockaddr_in HeWasNeverSeenAgain;//create socket adress to store in Vector
																ClientAddresses.push_back(HeWasNeverSeenAgain);//storing
																SocketLengths.push_back(sizeof(ClientAddresses[count]));//get the size of the stored address
																ClientFd.push_back(accept(sockfd, (struct sockaddr *) &ClientAddresses[count], &SocketLengths[count]));//taking a connection and extract it, store fd in vector
																user* tuess = new user();
																tuess->fill();
																(*mine).push_back(*tuess);
																changes.push_back(false);
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

								//
								// !!!TEST!!!
								//
								//(*mine)[counti].setBools(2,0);
								//
								//
								//
								std::thread *ClockThread = new std::thread(&Server::MagicalwhiteSmoke,this, counti);

								int fall = 0;
								int command = 0;
								int Position;
								//unsigned char bILD[BITBildSize];
								char Bool, Char;
								char Integer[4];
								char MLength[] = {0,0,0,0};
								bool Continue = true;
								while (true) {

																changes[counti] = true;

																switch (fall) {
																case 0: read(ClientFd[counti],&command,1);
																								fall = command;
																								break;
																case 1:
																								while (Continue)
																								{
																																read(ClientFd[counti],&command,1);
																																switch (command) {
																																default: std::cout << "wrong ab receving" << '\n';
																																								break;
																																case 3:  Continue = false;
																																								break;
																																case 100: read(ClientFd[counti],&Integer,4);
																																								(*mine)[counti].setID(CharInt(Integer));
																																								break;
																																case 101: do
																																								{
																																																read(ClientFd[counti], &Position, 1);
																																																if(Position == 253)
																																																{
																																																								break;
																																																}
																																																read(ClientFd[counti], &Integer, 4);
																																																(*mine)[counti].recieveInt((Integer[0] << 24)+(Integer[1] << 16)+(Integer[2] << 8)+Integer[3],Position);
																																								} while (true);
																																								break;
																																case 102: do
																																								{
																																																read(ClientFd[counti], &Position, 1);
																																																if(Position == 253)
																																																{
																																																								break;
																																																}
																																																read(ClientFd[counti], &Bool, 1);
																																																(*mine)[counti].recieveBool(Bool,Position);
																																								} while(true);
																																								break;
																																case 104: for(int i = 0; i < (*mine)[counti].getBITBildSize(); i++)
																																								{
																																																read(ClientFd[counti], &Char,1);//&bILD,BITBildSize);
																																																(*mine)[counti].recieveBITBild(Char,i);
																																								}
																																								break;
																																case 103:  (*mine)[counti].recieveMessage("");
																																								read(ClientFd[counti],&MLength,4);
																																								int RecivingLength = (MLength[0] << 24)+(MLength[1] << 16)+(MLength[2] << 8)+MLength[3];
																																								char MessagE [RecivingLength];
																																								read(ClientFd[counti],&MessagE,RecivingLength);
																																								std::string mESSAGe(MessagE,RecivingLength);
																																								(*mine)[counti].recieveMessage(mESSAGe);
																																								RecivingLength--;
																																								break;
																																}
																								}
																								Continue=true;
																								fall=0;
							#ifdef SERVER_STANDALONE
																								HQ->newData(counti);
							#endif
																								break;
																case 2: command = 200;
																								write(ClientFd[counti],&command,1);
																								char chaInt[4];
																								for (int i = 0; i < (*mine)[counti].getIntegerCount(); i++)
																								{
																																if ((*mine)[counti].getIntegersChanged(i)) {
																																								write(ClientFd[counti],&i,1);
																																								IntChar((*mine)[counti].transmitInt(i), chaInt);
																																								write(ClientFd[counti], chaInt, 4);
																																}
																								}
																								command = 253;
																								write(ClientFd[counti],&command,1);

																								command = 201;
																								write(ClientFd[counti], &command, CommandLength);//send to sockfd command 102 with length 1
																								for (int i = 0; i < (*mine)[counti].getBoolCount(); i++)
																								{
																																if ((*mine)[counti].getBoolChanged(i)) {
																																								write(ClientFd[counti],&i,1);
																																								char asdf = (*mine)[counti].transmitBool(i);
																																								write(ClientFd[counti], &asdf, 1);
																																}
																								}
																								command = 253;
																								write(ClientFd[counti],&command,1);
																								if((*mine)[counti].getMessageChanged())
																								{
																																command = 202;
																																write(ClientFd[counti], &command, CommandLength);//send to sockfd command 103 with length 1
																																//sent itnt for length
																																char charMessageLength[4] = {0,0,0,0};
																																IntChar((*mine)[counti].getMessageLength()+1,charMessageLength);
																																write(ClientFd[counti], charMessageLength, 4);
																																write(ClientFd[counti], (*mine)[counti].transmitMessage().c_str(), (*mine)[counti].getMessageLength()+1);
																								}

																								command = 003;
																								write(ClientFd[counti], &command, 1);
																								fall=0;
																								break;
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


int Server::recie(int fd,void *buf, size_t length)
{
								int ret = recv(fd, buf, length, MSG_DONTWAIT);
								if (ret < length) {//detect an error
																perror(NULL);//print error message
																//call reconection routine
								}
								return ret;
}

int Server::writi(int fd,void *buf, size_t length)
{
								send(fd, buf, length,0);
}

void Server::MagicalwhiteSmoke(int counti)
{
								int allowed_loops = 1000000;
								time_t last = clock();
								while (true) {
																if(last + allowed_loops < clock())
																{
																								mine->at(counti).setConnectionLost(true);
																								// std::cout << "/* message */ "<< counti << '\n';
																}
																if (changes[counti]) {
																								// std::cout << "/* message */" << '\n';
																								last = clock();
																								changes[counti] = false;
																								mine->at(counti).setConnectionLost(false);
																}
								}
}
