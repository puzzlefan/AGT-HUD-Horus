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

								mine = point;//safes pointer to users
	#ifdef SERVER_STANDALONE
								HQ = abc;//safes pointer to GUI
	#endif
								//SignalEmpfaenger = poinTI;
								sockfd = socket(AF_INET, SOCK_STREAM,0);//Creates a standart Socket ready for TCP
								if (sockfd<0)//validiti check
								{
																cout << "Socket Adresse ungültig" << '\n';
								}
								bzero((char *)&serv_addr, sizeof(serv_addr));//clearing the address for safety

								serv_addr.sin_family = AF_INET;//tells the socket to use the IP protocoll in this case it should be Version 4
								serv_addr.sin_addr.s_addr = INADDR_ANY;//tells the socket it's IP-Address in our case we just use that one we already have/ that it does not matter
								serv_addr.sin_port = htons(portno);//port selection

								if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) {//das betriebssysterm mit unserem Socket bekanntmachen, so dass es zu uns leiten kann
																std::cout << "error on binding" << '\n';
								}

								listen(sockfd,5);; //tells the system to listen for incoming requests and que them for us to a max length of 5 because why not 5

								//
								//starting the first thread, that one only handles acception of connection because it ohterwise would block the continuation of the programm
								//
								ServerMain = new thread(&Server::ServerMainThread,this);
								ClockThread = new std::thread(&Server::MagicalwhiteSmoke,this);//thread to detect timeouts


}

void Server::ServerMainThread()
{
								while (true) {
																struct sockaddr_in HeWasNeverSeenAgain;//create socket adress to store in Vector
																ClientAddresses.push_back(HeWasNeverSeenAgain);//storing
																SocketLengths.push_back(sizeof(ClientAddresses[count]));//get the size of the stored address
																ClientFd.push_back(accept(sockfd, (struct sockaddr *) &ClientAddresses[count], &SocketLengths[count]));//taking a connection and extract it, store fd in vector

																//giving the connection a "user"
																user* tuess = new user();
																tuess->fill();//used to clear should live in constructer
																(*mine).push_back(*tuess);

																//addng timing thread unsafe, safety is not necesarry
																changes.push_back(true);
																last.push_back(clock());

																//detectz if the connection is for real, user variables are generated before, to stay in sync with count
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
								int fall = 0;//used for navigation
								bool Continue = true;//used to break out of a loop
								char command;//holds the commands
								//dai
								//std::thread *ClockThread = new std::thread(&Server::MagicalwhiteSmoke,this, counti);

								while (true) {
																changes[counti] = true;//ugly timeout prevention

																switch (fall) {//navigator
																case 0:	{ //get initial command
																								read(ClientFd[counti],&command,1);//get commad from client
																								fall = command;//pipe it through
																								break;
																				}
																case 1:	{	//recieve data
																								while (Continue)//runs still stob "bit" is recied
																								{
																																read(ClientFd[counti],&command,1);//getting which data is going to be send
																																switch (command) {
																																default:	{	//everything else
																																						std::cout << "wrong ab receving" << '\n';
																																						break;
																																				}
																																case 3: 	{//when client has send the stop byte
																																 						Continue = false;
																																						break;
																																				}
																																case 100:	{//get an ID
																																						getID(counti);
																																						break;
																																					}
																																case 101:	{
																																						getIntegers(counti);
																																						break;
																																					}
																																case 102:	{
																																						getBools(counti);
																																						break;
																																					}
																																case 104:	{
																																	 					getBild(counti);
																																						break;
																																					}
																																case 103:	{
																																						getMessage(counti);
																																						break;
																																					}
																																}
																								}
																								Continue=true;//gets ready for the next round
																								fall=0;//makes ready for next command
																								#ifdef SERVER_STANDALONE
																									HQ->newData(counti);//tells the Gui the new Data
																								#endif
																								break;
																				}
																case 2: {	//send data
																								setIntegers(counti);
																								setBools(counti);
																								setMessage(counti);
																								endOfServerData(counti);
																								fall=0;//return to step one
																								break;
																				}
																default:	{
																								std::cout << "something went wrong during sending, I probably want to dai" << '\n';
																				}
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


void Server::MagicalwhiteSmoke()// a bit mäh
{
								int allowed_loops = 1000000;
								//time_t last = clock();
								while (true) {
									for(int i = 0; i < last.size();i++)//not thread safe
									{
																if(last[i] + allowed_loops < clock())
																{
																								mine->at(i).setConnectionLost(true);
																								// std::cout << "/* message */ "<< counti << '\n';
																}
																if (changes[i]) {
																								// std::cout << "/* message */" << '\n';
																								last[i] = clock();
																								changes[i] = false;
																								mine->at(i).setConnectionLost(false);
																}
									}
								}
}


void Server::setIntegers(int counti)
{
	char command = 200; //tells client that the integers will follow
	char chaInt[4];//holds the integers as for chars
	write(ClientFd[counti],&command,1);//does the telling
	for (int i = 0; i < (*mine)[counti].getIntegerCount() ; i++)//goes throw every int
	{
		if ((*mine)[counti].getIntegersChanged(i)) {//only sends new one when it has changed
			write(ClientFd[counti],&i,1);//tells the Client the index of the actual int limited to 200
			IntChar((*mine)[counti].transmitInt(i), chaInt);//transforms to 4 chars
			write(ClientFd[counti], chaInt, 4);//sends the int as chars
		}
	}
	command = 253;//sends the abortion command
	write(ClientFd[counti],&command,1);//does the sending
}
void Server::setBools(int counti)
{
	char command = 201;//tells to send bools
	write(ClientFd[counti], &command, CommandLength);//sending
	for (int i = 0; i < (*mine)[counti].getBoolCount(); i++)//loop through all
	{
									if ((*mine)[counti].getBoolChanged(i)) {//only transfer changed up to 200
																	write(ClientFd[counti],&i,1);//send imdex
																	char boolDisguisedAsChar = (*mine)[counti].transmitBool(i);//safes the bool value in a char
																	write(ClientFd[counti], &boolDisguisedAsChar, 1);//sends bool
									}
	}
	command = 253;//tells there are no more bools
	write(ClientFd[counti],&command,1);//telling
}
void Server::setMessage(int counti)
{
	char command;//holds the commands
	if((*mine)[counti].getMessageChanged())//only does something when the message has changed
	{
									char charMessageLength[4] = {0,0,0,0}; //prepares integer holding char array
									command = 202;//tells to send a message
									write(ClientFd[counti], &command, CommandLength);//sending
									IntChar((*mine)[counti].getMessageLength()+1,charMessageLength);//converts the message length plus one for the the null-termination to 4 chars
									write(ClientFd[counti], charMessageLength, 4);//sends messaghe length
									write(ClientFd[counti], (*mine)[counti].transmitMessage().c_str(), (*mine)[counti].getMessageLength()+1);//send Message
	}
}
void Server::endOfServerData(int counti)
{
	char command = 003;//code for no more dat to be send
	write(ClientFd[counti], &command, 1);	//sending
}

void Server::getID(int counti)
{
	char Integer[4];
	read(ClientFd[counti],&Integer,4);//read the value
	(*mine)[counti].setID(CharInt(Integer));//store the value
}
void Server::getIntegers(int counti)
{
	char Position;
	char Integer[4];
	do
			{
											read(ClientFd[counti], &Position, 1);//read first instruction
											if(Position == 253)//if equal 253 there is no more new data
											{
																			break;
											}
											read(ClientFd[counti], &Integer, 4);//otherwise read int as for chars
											(*mine)[counti].recieveInt((Integer[0] << 24)+(Integer[1] << 16)+(Integer[2] << 8)+Integer[3],Position);//and storing it
			} while (true);
}
void Server::getBools(int counti)
{
	char Position, Bool;
	do
	{
											read(ClientFd[counti], &Position, 1);//read command
											if(Position == 253)//when equal 253 stop
											{
																			break;
											}
											read(ClientFd[counti], &Bool, 1);//otherwise use as index and read bool
											(*mine)[counti].recieveBool(Bool,Position);//store bool
	} while(true);
}
void Server::getBild(int counti)
{
	char Char;
	for(int i = 0; i < (*mine)[counti].getBITBildSize(); i++)//index is to big and picture changes to much as that partly transfer would bring any good
	{
									read(ClientFd[counti], &Char,1);//read one
									(*mine)[counti].recieveBITBild(Char,i);//store one
	}
}
void Server::getMessage(int counti)
{
	char MLength[] = {0,0,0,0};//char storage
	(*mine)[counti].recieveMessage("");//clears message
	read(ClientFd[counti],&MLength,4);//gets message length
	int RecivingLength = (MLength[0] << 24)+(MLength[1] << 16)+(MLength[2] << 8)+MLength[3];//converts length to do something usefull
	char MessagE [RecivingLength];//for example create the char array which will hold the transmitted char array
	read(ClientFd[counti],&MessagE,RecivingLength);//getting char array
	std::string mESSAGe(MessagE,RecivingLength);//convert to string
	(*mine)[counti].recieveMessage(mESSAGe);//storing string
}
