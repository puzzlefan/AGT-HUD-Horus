#include <stdio.h>      //(C) STanaDart Input Output library (still works in ++) used for interaction with filesytem, keybord ... via stzreams which are associatet with pointers in the filesystem
#include <stdlib.h>     //Standart Bibliothek
#include <unistd.h>     //System interaction, probably
#include <string.h>     //handling of strings and Arrays
#include <sys/types.h>  //introduces more data types (probabl derived ones which make things easier)
#include <sys/socket.h> //socket library accept...
#include <netinet/in.h> //structs for sockets
#include <string>
#include <thread>
#include <iostream>
#include "../User/User.h"
#include "client.h"

int main(int argc, char const *argv[]) {
        user a;
        Client kop(&a);

        a.setID(1);
        a.setBools(0,1);
        std::string text = "";
        while (true)
        {
                std::cin >> text;
                a.setMessage(text);
        }
        return 0;
}
