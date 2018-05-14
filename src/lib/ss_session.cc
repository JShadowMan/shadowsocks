#include "shadowsocks/ss_core.h"
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

        // receive data from socket to package buffers
        auto insertPtr = BUFFER_GET_INSERT_POINTER(buffer);
        auto bufferAvailableSize = BUFFER_AVAILABLE_SIZE(buffer);
        count = recv(_clientSocket, insertPtr, bufferAvailableSize, 0);
        // update buffer size
        _package.updateBuffer(count);
        // check has complete package
        while (_package.hasPackage()) {
            // decrypt package and send request, response receive to outputs
        }

        // receive complete or connection closed
        if (count != bufferAvailableSize) {
            // connection closed
            if (count == 0) {
                throw SessionClosed();
            } else if (count == -1) {
                checkSessionError();
            }

            break;
        }
    } while (true);

    std::cout << _package;
}

// session writable
void Ss_Session::writableHandle() {
    // not handle anytime
    std::cout << _clientSocket << " writable" << std::endl;
}

// when session receive data error occurs
void Ss_Session::checkSessionError() {
#ifdef __linux__
    // do nothing on linux


#elif __windows__
    switch (WSAGetLastError()) {
        case CONNECTION_RESET_BY_PEER:
            throw SessionClosed();
        default: {
            std::stringstream ss;
            ss << "window socket error: " << WSAGetLastError() << std::endl;
            Ss_Core::printLastError(ss.str().c_str());
            std::exit(1);
        }
    }


#endif

    // Ss_Session::checkSessionError
}
