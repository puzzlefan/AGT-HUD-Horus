#ifndef SERVER_H
#define SERVER_H

class Server
{
private:
	//Vars for the main thread
	int sockfd, protno;
public:
	Server();
	~Server();
};

#endif