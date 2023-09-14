#pragma once

#include <string>
#include <chrono>
#include "Sender.hpp"
#include "Datagram.hpp"

class TrafficGenerator
{
    public:
        TrafficGenerator(Sender* sender, unsigned int rate, unsigned int mtu);
        ~TrafficGenerator();
        void run(unsigned int executionTime);

    private:
        Sender* sender;
        unsigned int rate;
        unsigned int mtu;
        Datagram* datagram;
        float packetsPerSecond;
        std::chrono::microseconds intervalBetweenPackets;
};
