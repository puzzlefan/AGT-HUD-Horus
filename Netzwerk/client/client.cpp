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
//#include "../User/User.h"
#include <sys/time.h>//macht zeit
#include <sys/select.h>
#include "client.h"

Client::Client(user *point /*, HeadGUI *PointerHeadGUI*/)
{
        std::signal(SIGPIPE, SIG_IGN);//let write errors dont crash the programm

        mine = point;
        //GUI = PointerHeadGUI;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);//open client socket end check if it worked
        if (sockfd<0) {
                std::cout << "error opening socket" << '\n';
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));//making endpoint socket identifaier ready
        serv_addr.sin_family = AF_INET;//ist im internet
        inet_pton(AF_INET, "192.168.178.32", &(serv_addr.sin_addr));
        //inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));//IP Adresse da wir Rasoberry Pi als Router verwenden ist diese Fix bei solange nur eine Testmaschine 127.0.0.1
        serv_addr.sin_port = htons(portno);

        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
                std::cout<<"ERROR connecting Netzwerk client"<<"\n";
                return;
        }

        ClientThread = new std::thread(&Client::communicator,this);
        ClockThread = new std::thread(&Client::MagicalwhiteSmoke,this);
}

Client::~Client()
{
        close(sockfd);
}

void Client::communicator()
{
        bool id_confirmed = false;//bool for blocking data while waiting
        char command = 0;//short time storage of commands
        int fall = 0;//short time storage of next Step

        while (1!=2)//endless loop
        {
                change = true;//sets the bool for the counter to true to reset the counter
                switch (fall) {
                case 0:   if(id_confirmed || mine->getBool(NEW_CONFIRMED_ID))
                        {
                                fall = 1;//activates first order
                        }
                        else
                        {
                                fall = 0;//continue until an id has been confirmed
                        }
                        break;
                case 1:   command = 001;
                        writi(sockfd, &command, CommandLength);//send to sockfd command 1 with length 1
                        fall = 100;
                        break;

                case 2:   command = 002;
                        writi(sockfd, &command, CommandLength);//send to sockfd command 2 with length 1
                        char Position;
                        char Bool;
                        char Char;
                        char Integer[4];
                        int RecivingLength;
                        do
                        {
                                recie(sockfd, &command, CommandLength);
                                switch (command) {
                                default: //std::cout << "something went horrible wrong through out reading" << '\n';
                                        break;
                                case 3:     break;
                                case 200:   do
                                        {
                                                recie(sockfd, &Position, 1);
                                                if(Position == 253)
                                                {
                                                        break;
                                                }
                                                recie(sockfd, &Integer, 4);
                                                mine->recieveInt((Integer[0] << 24)+(Integer[1] << 16)+(Integer[2] << 8)+Integer[3],Position);
                                        } while(true);
                                        break;
                                case 201:   do
                                        {
                                                recie(sockfd, &Position, 1);
                                                if(Position == 253)
                                                {
                                                        break;
                                                }
                                                recie(sockfd, &Bool, 1);
                                                mine->recieveBool(Bool,Position);
                                        } while(true);
                                        break;
                                case 202:   mine->recieveMessage("");
                                        char MLength[4] = {0,0,0,0};
                                        recie(sockfd,&MLength,4);
                                        RecivingLength = (MLength[0] << 24)+(MLength[1] << 16)+(MLength[2] << 8)+MLength[3];
                                        char MessagE [RecivingLength];
                                        //for (int i = 0; i < mine->getMessageLength(); i++)
                                        //{
                                        recie(sockfd,&MessagE,RecivingLength);
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
                        writi(sockfd, &command, CommandLength);//send to sockfd command 3 with length 1
                        fall = 002;
                        break;

                case 100: command = 100;
                        writi(sockfd, &command, CommandLength);//send to sockfd command 100 with length 1
                        char charID[4];
                        IntChar(mine->getID(),charID);
                        writi(sockfd, charID, 4);
                        fall = 101;
                        break;

                case 101: command = 101;
                        writi(sockfd, &command, CommandLength);//send to sockfd command 101 with length 1
                        char chaInt[4];
                        for (char i = 0; i < mine->getIntegerCount(); i++)
                        {
                                if (mine->getIntegersChanged(i)) {
                                        writi(sockfd,&i,1);
                                        IntChar(mine->transmitInt(i), chaInt);
                                        writi(sockfd, chaInt, 4);
                                }
                        }
                        command = 253;
                        writi(sockfd,&command,1);
                        fall = 102;
                        break;

                case 102: command = 102;
                        writi(sockfd, &command, CommandLength);//send to sockfd command 102 with length 1
                        for (char i = 0; i < mine->getBoolCount(); i++)
                        {
                                if (mine->getBoolChanged(i)) {
                                        writi(sockfd,&i,1);
                                        char asdf = mine->transmitBool(i);
                                        writi(sockfd, &asdf, 1);
                                }
                        }
                        command = 253;
                        writi(sockfd,&command,1);
                        fall = 103;
                        break;

                case 103: if(mine->getMessageChanged())
                        {
                                command = 103;
                                writi(sockfd, &command, CommandLength);//send to sockfd command 103 with length 1
                                //sent itnt for length
                                char charMessageLength[4];
                                IntChar(mine->getMessageLength()+1,charMessageLength);
                                writi(sockfd, charMessageLength, 4);
                                //for(int i = 0; i< mine->getMessageLength();i++)
                                //{
                                writi(sockfd, mine->transmitMessage().c_str(), mine->getMessageLength()+1);
                                //}
                        }
                        fall = 104;
                        break;

                case 104: command = 104;//needs change
                        writi(sockfd, &command, CommandLength);//send to sockfd command 104 with length 1
                        for(int i = 0; i< mine->getBITBildSize(); i++)
                        {
                                char ToWrite = mine->transmitBITBild(i);
                                writi(sockfd, &ToWrite, 1);//send to sockfd command 104 with length 1
                        }
                        mine->setBools(UPDATE_IMAGE_SIGNAL,true);
                        fall = 003;
                        break;
                default: //std::cout << "something wemt horrebly wrong" << '\n';
                        break;
                }
        }
}

bool Client::readable()
{
        fd_set rfds;//generates buffers which hold the sockets for select to check
        struct timeval WaitingTime;
        //specifais the time select waits for data select returns in struct length of unwaitet time but since it is zero ...
        WaitingTime.tv_sec = 0;
        WaitingTime.tv_usec = 0;

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
        fd_set wfds;//generates buffers which hold the sockets for select to check

        struct timeval WaitingTime;
        //specifais the time select waits for data select returns in struct length of unwaitet time but since it is zero ...
        WaitingTime.tv_sec = 0;
        WaitingTime.tv_usec = 0;

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

int Client::recie(int fd, void *buf, size_t length)
{
        int ret = recv(fd, buf, length, MSG_WAITALL);
        if (ret < length) {//detect an error
                perror(NULL);//print error message
                //call reconection routine
        }
        return ret;
}

int Client::writi(int fd,const void *buf, size_t length)
{
        return send(fd, buf, length,0);
}

void Client::MagicalwhiteSmoke()
{
        int allowed_loops = 1000000;
        time_t last = clock();
        while (true) {
                if(last + allowed_loops < clock())
                {
                        mine->setConnectionLost(true);
                        // std::cout << "/* message */" << '\n';
                }
                if (change) {
                        // std::cout << "/* message */" << '\n';
                        last = clock();
                        change = false;
                        mine->setConnectionLost(false);
                }
        }
}
int Client::reconnect()
{
        protocolReboot = true;
        retryCount++;

        //basicly completly reconfigures socket
        //
        //actualy testing if this is realy needet
        //

/*
   sockfd = socket(AF_INET, SOCK_STREAM, 0);//open client socket end check if it worked
   if (sockfd<0) {
    std::cout << "error opening socket" << '\n';
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));//making endpoint socket identifaier ready
   serv_addr.sin_family = AF_INET;//ist im internet
   //inet_pton(AF_INET, "192.168.2.50", &(serv_addr.sin_addr));
   inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));//IP Adresse da wir Rasoberry Pi als Router verwenden ist diese Fix bei solange nur eine Testmaschine 127.0.0.1
   serv_addr.sin_port = htons(portno);
 */
        if(retryCount < 1000000000)
        {
                if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
                {
                        std::cout<<"ERROR connecting Netzwerk client"<<"\n";
                        reconnect();
                        return -1;
                }
        }
        return 0;
}
