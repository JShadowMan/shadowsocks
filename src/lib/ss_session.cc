#include <iostream>
#include "shadowsocks/ss_session.h"


// Ss_Session constructor
Ss_Session::Ss_Session(SOCKET s): _clientSocket(s) {
    std::cout << "new session: " << _clientSocket << std::endl;
}

// clean session data
Ss_Session::~Ss_Session() {
    std::cout << "session destructor" << std::endl;
}

// session readable
void Ss_Session::readableHandle() {
    int count = 0;

    do {
        Ss_Package::Buffer &buffer = _package.getBuffer();

        count = recv(_clientSocket, BUFFER_GET_INSERT_POINTER(buffer),
                     BUFFER_AVAILABLE_SIZE(buffer), 0);

        // check socket buffer
        if (count != BUFFER_AVAILABLE_SIZE(buffer)) {
            // connection closed
            if (count == 0) {
                throw SessionClosed();
            }

            _package.update(count);
            break;
        }

        // allocate next block
        _package.update();
    } while (true);

    std::cout << _package;
}

// session writable
void Ss_Session::writableHandle() {
    // not handle anytime
    std::cout << _clientSocket << " writable" << std::endl;
}
