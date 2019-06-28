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
    milliseconds intervalBetweenPackets = milliseconds((int) (1000/packetsPerSecond));

    cout << "Programa enviará " << packetsPerSecond << " pacote(s) de " << this->mtu << " bytes por segundo." << endl;
    cout << "Isto é, um pacote a cada " << intervalBetweenPackets.count() << " milisegundo(s)." << endl;
    cout << "Programa parará em " << executionTime << " segundos." << endl;
    cout << "Gerando tráfego..." << endl;

    milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    milliseconds maxTime = currentTime + milliseconds(executionTime*1000);
    milliseconds targetTime = currentTime + intervalBetweenPackets;

    while(currentTime < maxTime) {
        currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        if(currentTime >= targetTime) {
            targetTime += intervalBetweenPackets;
            this->sender->send(this->datagram);
        }
    }

    cout << "Parando de gerar tráfego..." << endl;
}
