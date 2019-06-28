#include <string>
#include <iostream>
#include "Datagram.hpp"
#include "Sender.hpp"
#include "TrafficGenerator.hpp"

using namespace std;

TrafficGenerator::TrafficGenerator(Sender* sender, unsigned int rate, unsigned int mtu) {
    this->sender = sender;
    this->rate = rate;
    this->mtu = mtu;
    this->datagram = Datagram::generateRandom(mtu);
}

TrafficGenerator::~TrafficGenerator() {
    delete this->sender;
    delete this->datagram;
}

void TrafficGenerator::run() {
    this->sender->send(this->datagram);
}
