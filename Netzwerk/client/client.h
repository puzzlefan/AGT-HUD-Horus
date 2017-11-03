#ifndef CLIENT_H
#define CLIENT_H

class Client
{
private://the ip adress of the server stands in the cpp fron the client because if it stands around the other variables it wont compile
  size_t CommandLength = 1;

  int sockfd;
  uint16_t portno = 42000;
  struct sockaddr_in serv_addr;
  std::thread *ClientThread;

  user mine;
public:
  Client();
  ~Client();

  void communicator();
  void communicationWithTheCommunicator();

  void rwteble(bool *ari);
  void IntChar(int Inte, char *ptr);
};

#endif
