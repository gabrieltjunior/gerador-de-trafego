#pragma once

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Datagram.hpp"

class Sender
{
    public:
        Sender(std::string ip, unsigned int port);
        void send(Datagram* datagram);
        ~Sender();

    private:
        int socketDescriptor;
        struct sockaddr_in toAddress;
        std::string ip;
        unsigned int port;
};
