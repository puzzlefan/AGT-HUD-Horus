#include <stdio.h>      //(C) STanaDart Input Output library (still works in ++) used for interaction with filesytem, keybord ... via stzreams which are associatet with pointers in the filesystem
#include <stdlib.h>     //Standart Bibliothek
#include <string.h>     //handling of strings and Arrays
#include <unistd.h>     //System interaction, probably
#include <sys/types.h>  //introduces more data types (probabl derived ones which make things easier)
#include <sys/socket.h> //socket library accept...
#include <netinet/in.h> //structs for sockets
#include <thread>
#include <vector>
#include <iostream>
#include "../User/User.h"
#include "server.h"

int main(void)
{
	std::vector<user> v;
	Server ItsMe(&v);

	std::string text= "";
	std::string last = "";
	while(v.size()<=0);
	while (true)
	{
		if(last != v[0].getMessage())
		{
			std::cout << v[0].getMessage() << '\n';
			last = v[0].getMessage();
		}
	}
	return 0;
}
