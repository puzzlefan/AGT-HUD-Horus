#ifndef SERVER_H
#define SERVER_H

class Server
{
private:
	//Vars for the main thread
	int sockfd;
	uint16_t portno = 42;
	struct sockaddr_in serv_addr;

	std::thread *ServerMain;
	std::vector<std::thread> clientThreads;
public:
	Server();
	~Server();

	int ServerMainThread();//{return 1;}
};

#endif
