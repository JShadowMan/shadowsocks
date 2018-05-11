#include <iostream>
#include "shadowsocks/ss_session.h"


// Ss_Session constructor
Ss_Session::Ss_Session(SOCKET s): _clientSocket(s) {
    std::cout << "new session: " << _clientSocket << std::endl;
}

// session readable
void Ss_Session::readableHandle() {
    int count = 0;

    do {
        Ss_Package::Package &package = _package.get();

        auto insertPos =  package.first + package.second;
        auto lessCount = Ss_Package::PACKAGE_SIZE - package.second;
        count = recv(_clientSocket, insertPos, lessCount, 0);
        if (count != lessCount) {
            _package.update(count);
            break;
        }
        _package.update();
    } while (true);

    std::cout << _package;
}

// session writable
void Ss_Session::writableHandle() {
    // not handle anytime
    std::cout << _clientSocket << " writable" << std::endl;
}
