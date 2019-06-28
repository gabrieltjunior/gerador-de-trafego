#pragma once

#include <string>
#include "Sender.hpp"
#include "Datagram.hpp"

class TrafficGenerator
{
    public:
        TrafficGenerator(Sender* sender, unsigned int rate, unsigned int mtu);
        ~TrafficGenerator();
        void run();

    private:
        Sender* sender;
        unsigned int rate;
        unsigned int mtu;
        Datagram* datagram;
};
