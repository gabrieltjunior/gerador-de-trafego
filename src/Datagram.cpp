#include <string>
#include "Datagram.hpp"

using namespace std;

Datagram::Datagram(string content) {
    this->content = content;
    this->length = content.length();
    this->cString = content.c_str();
}

Datagram* Datagram::generateRandom(const unsigned int size) {
    static const char allowedCharacters[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    static const unsigned int allowedCharactersSize = sizeof(allowedCharacters) - 1;

    string generatedString;

    for (unsigned int i = 0; i < size; i++) {
        generatedString += allowedCharacters[rand() % allowedCharactersSize];
    }

    return new Datagram(generatedString);
}

string Datagram::getContent() {
    return this->content;
}

unsigned int Datagram::getLength() {
    return this->length;
}

const char* Datagram::getCString() {
    return this->cString;
}
