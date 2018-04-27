#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shadowsocks/ss_network.h"


// Ss_network constructor
Ss_Network::Ss_Network()
    : Ss_Network(INET4) {
}

// Ss_Network constructor
Ss_Network::Ss_Network(NetworkFamily family)
    : _family(family) {
}

// destructor: close network
Ss_Network::~Ss_Network() {
    close(_socket);
    std::cout << "Socket: " << _socket << " closed." << std::endl;
}

// create listen socket
bool Ss_Network::listen(const char *host, int port) {
    if (!createSocket(host)) {
        std::cout << "Create socket error" << std::endl;
    }

    return true;
}

// create socket and setup
bool Ss_Network::createSocket(const char *host) {
    _socket = socket(_family, SOCK_STREAM, 0);
    std::cout << _socket << std::endl;
    return true;
}
