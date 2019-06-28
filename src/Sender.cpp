#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Sender.hpp"
#include "Datagram.hpp"

using namespace std;

Sender::Sender(std::string ip, unsigned int port) {
    this->ip = ip;
    this->port = port;

    struct hostent *host = gethostbyname(ip.c_str());

    if ((this->socketDescriptor = ::socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		cout << "ERROR opening socket" << endl;
        exit(1);
    }

	this->toAddress.sin_family = AF_INET;
	this->toAddress.sin_port = htons(port);
	this->toAddress.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(this->toAddress.sin_zero), 8);
}

void Sender::send(Datagram* datagram) {
    int n = sendto(
        this->socketDescriptor,
        datagram->getCString(),
        datagram->getLength(),
        0,
        (const struct sockaddr *) &(this->toAddress),
        sizeof(struct sockaddr_in)
    );
	if (n < 0){
		cout << "ERROR sending data" << endl;
        exit(1);
    }
}

Sender::~Sender() {
    close(this->socketDescriptor);
}
