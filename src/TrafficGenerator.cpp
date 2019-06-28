#include <string>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include "Datagram.hpp"
#include "Sender.hpp"
#include "TrafficGenerator.hpp"

using namespace std;
using namespace std::chrono;

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

void TrafficGenerator::run(unsigned int executionTime) {
    float packetsPerSecond = (rate*1000)/(mtu*8);
    microseconds intervalBetweenPackets = microseconds((int) (1000000/packetsPerSecond));

    cout << "Programa enviará " << packetsPerSecond << " pacote(s) de " << this->mtu << " bytes por segundo." << endl;
    cout << "Isto é, um pacote a cada " << intervalBetweenPackets.count() << " microsegundo(s)." << endl;
    cout << "Programa parará em " << executionTime << " segundos." << endl;
    cout << "Gerando tráfego..." << endl;

    microseconds currentTime = duration_cast<microseconds>(system_clock::now().time_since_epoch());
    microseconds maxTime = currentTime + microseconds(executionTime*10000000);
    microseconds targetTime = currentTime + intervalBetweenPackets;

    while(currentTime < maxTime) {
        currentTime = duration_cast<microseconds>(system_clock::now().time_since_epoch());
        if(currentTime >= targetTime) {
            targetTime += intervalBetweenPackets;
            this->sender->send(this->datagram);
        }
    }

    cout << "Parando de gerar tráfego..." << endl;
}
