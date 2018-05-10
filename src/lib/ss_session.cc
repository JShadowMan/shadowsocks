#include <iostream>
#include "shadowsocks/ss_session.h"


// Ss_Session constructor
Ss_Session::Ss_Session(SOCKET s):
    _clientSocket(s) {

    std::cout << "new session: " << _clientSocket << std::endl;
}

// session readable
void Ss_Session::readableHandle() {
    if (bufferSizeGreatThan(2)) {
        auto header = fetchBuffer(2);
        std::cout << header << std::endl;
    }
}

// session writable
void Ss_Session::writableHandle() {
    // not handle anytime
    std::cout << _clientSocket << " writable" << std::endl;
}

// cat tcp/udp buffer
std::shared_ptr<u_char> Ss_Session::peekBuffer(int length) {
    auto *data = new u_char[length];
    memset(data, 0, sizeof(u_char) * length);

    int count = 0;
    count = ::recv(_clientSocket, (char*)(data), length, MSG_PEEK);
    if (count != length) {
        delete[] data;
        return std::shared_ptr<u_char>(nullptr);
    }
    return std::shared_ptr<u_char>(data);
}

// check buffer size valid
bool Ss_Session::bufferSizeGreatThan(int length) {
    return peekBuffer(length) != nullptr;
}

// from buffer fetch data
std::shared_ptr<u_char> Ss_Session::fetchBuffer(int length) {
    auto *data = new u_char[length];
    memset(data, 0, sizeof(u_char) * length);

    ::recv(_clientSocket, (char*)(data), length, 0);
    return std::shared_ptr<u_char>(data);
}
