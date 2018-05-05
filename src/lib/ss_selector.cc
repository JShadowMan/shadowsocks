#include <map>
#include <cstdlib>
#include <iostream>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_selector.h"


// Ss_Selector constructor
Ss_Selector::Ss_Selector(SelectorCallback &cb)
    : _callback(cb) {
}

// register a socket to selector
void Ss_Selector::registerSocket(SOCKET s, SelectorEvents events) {
    for (auto event : events) {
        // check SOCKET exists on map
        if (_sockets.find(s) == _sockets.end()) {
            _sockets[s] = SELECTOR_VALUE_INIT(s);
        }

        SELECTOR_VALUE_ADD(_sockets[s], static_cast<int>(event));
    }
}

// start select all socket descriptor
#ifdef __linux__
// on linux, `poll/epoll` available
void Ss_Selector::select() {
    pollfd *fds = new pollfd[_sockets.size()];

    int index = 0;
    for (auto &s : _sockets) {
        fds[index++] = s.second;
    }

    int total = ::poll(fds, _sockets.size(), -1);
    if (total == OPERATOR_FAILURE) {
        Ss_Core::printLastError("poll failure");
        std::exit(1);
    }

    if (total == 0) {
        std::cout << "poll time out" << std::endl;
    } else {
        int size = _sockets.size();
        for (index = 0; index < size && total > 0; index++) {
            if (fds[index].revents != 0) {
                if (fds[index].revents & SELECTOR_EVENT_IN) {
                    _callback(fds[index].fd, SelectorEvent::SE_READABLE);
                }

                if (fds[index].revents & SELECTOR_EVENT_OUT) {
                    _callback(fds[index].fd, SelectorEvent::SE_WRITABLE);
                }

                --total;
            }
        }
    }
}


#elif __windows__
// on windows, only `select` available
void Ss_Selector::select() {
    FD_SET readable = {0};
    FD_SET writable = {0};

    FD_ZERO(&readable);
    FD_ZERO(&writable);

    for (auto &s : _sockets) {
        if (s.second & SELECTOR_EVENT_IN) {
            FD_SET(s.first, &readable);
        }

        if (s.second & SELECTOR_EVENT_OUT) {
            FD_SET(s.first, &writable);
        }
    }

    int total = ::select(FD_SETSIZE, &readable, &writable, nullptr, nullptr);
    if (total == SOCKET_ERROR) {
        Ss_Core::printLastError("select error occurs");
        std::exit(1);
    }

    for (auto &s : _sockets) {
        if (total <= 0) {
            break;
        }

        if (FD_ISSET(s.first, &readable)) {
            --total;
            _callback(s.first, SelectorEvent::SE_READABLE);
        } else if (FD_ISSET(s.first, &writable)) {
            --total;
            _callback(s.first, SelectorEvent::SE_WRITABLE);
        }
    }
}


#endif