#include <cstdlib>
#include <map>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_selector.h"


// Ss_Selector constructor
Ss_Selector::Ss_Selector(SelectorCallback &cb)
    : _callback(cb) {
}

// register a socket to selector
void Ss_Selector::registerSocket(SOCKET s, SelectorEvents events) {
    for (auto event : events) {
        switch (event) {
            case SelectorEvent::SE_READABLE:
#ifdef __linux__
                _sockets[s] = { .fd = s, .events = POLLIN};
                break;
#elif __windows__
                _readable.push_back(s);
                break;
#endif


            case SelectorEvent::SE_WRITABLE:
#ifdef __linux__
                _sockets[s] = { .fd = s, .events = POLLOUT};
                break;
#elif __windows__
                _writable.push_back(s);
                break;
#endif
        }
    }
}

// start select all socket descriptor
#ifdef __linux__
// on windows, only `select` available
void Ss_Selector::select() {
}


#elif __windows__
// on linux, `poll/epoll` available
void Ss_Selector::select() {
    FD_SET readable = {0};
    FD_SET writable = {0};

    FD_ZERO(&readable);
    FD_ZERO(&writable);

    for (SOCKET s : _readable) {
        FD_SET(s, &readable);
    }

    for (SOCKET s : _writable) {
        FD_SET(s, &writable);
    }

    int total = ::select(0, &readable, &writable, nullptr, nullptr);
    if (total == SOCKET_ERROR) {
        Ss_Core::printLastError("select error occurs");
        std::exit(1);
    }

    for (SOCKET s : _readable) {
        if (FD_ISSET(s, &readable)) {
            _callback(s, SelectorEvent::SE_READABLE);
        }
    }

    for (SOCKET s : _writable) {
        if (FD_ISSET(s, &writable)) {
            _callback(s, SelectorEvent::SE_WRITABLE);
        }
    }
}


#endif