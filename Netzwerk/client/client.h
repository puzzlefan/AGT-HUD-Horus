#ifndef CLIENT_H
#define CLIENT_H

class Client
{
private://the ip adress of the server stands in the cpp fron the client because if it stands around the other variables it wont compile
  int sockfd;
  uint16_t portno = 42000;
  struct sockaddr_in serv_addr;
  std::thread *ClientThread;
public:
  Client();
  ~Client();

  void communicator();
  void communicationWithTheCommunicator();
};

#endif
