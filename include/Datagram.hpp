#pragma once

#include <string>

class Datagram
{
    public:
        Datagram(std::string content);
        std::string getContent();
        unsigned int getLength();
        const char* getCString();
        static Datagram* generateRandom(const unsigned int size);

    private:
        std::string content;
        unsigned int length;
        const char* cString;
};
