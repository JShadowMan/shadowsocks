#ifndef __SHADOWSOCKS_TYPES_INCLUDED__
#define __SHADOWSOCKS_TYPES_INCLUDED__
#pragma once


// standard libraries
#include <map>
#include <list>
#include <memory>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <initializer_list>


// types definition
#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/epoll.h>

#define SOCKET                          int
#define SELECTOR_KEY                    SOCKET
#define SELECTOR_VALUE                  pollfd
#define SELECTOR_EVENT_IN               POLLIN
#define SELECTOR_EVENT_OUT              POLLOUT

#define SELECTOR_VALUE_INIT(_S)         { .fd = (_S), .events = 0 }
#define SELECTOR_VALUE_ADD(_V, _E)      (_V).events |= (_E)


#elif __windows__
#include <Windows.h>
#include <WinSock2.h>

#define SOCKET                          SOCKET
#define SELECTOR_KEY                    SOCKET
#define SELECTOR_VALUE                  int
#define SELECTOR_EVENT_IN               1
#define SELECTOR_EVENT_OUT              2

#define SELECTOR_VALUE_INIT(_S)         (0)
#define SELECTOR_VALUE_ADD(_V, _E)      (_V) |= (_E)


#endif /* socket headers end */


// operator flags
#define OPERATOR_SUCCESS                (0)
#define OPERATOR_FAILURE                (-1)


// socket error flag
#ifndef SOCKET_ERROR
#define SOCKET_ERROR                    OPERATOR_FAILURE


#endif /* socket error flag end */


// session error flags
#define CONNECTION_RESET_BY_PEER       (10054)



// callback flag
#define CALLBACK_ACCESS                 public
#define SELECTOR_CALLBACK               CALLBACK_ACCESS
#define SESSION_CALLBACK                CALLBACK_ACCESS


// Buffer
#define BUFFER_SIZE                     (4 * 1024)
#define BUFFER_PRINT_SIZE               (8)
#define BUFFER_GET_POINTER(_B)          ((_B).first)
#define BUFFER_GET_SPEC_POINTER(_B, _N) (BUFFER_GET_POINTER(_B) + (_N))
#define BUFFER_GET_SIZE(_B)             ((_B).second)
#define BUFFER_GET_INSERT_POINTER(_B)   ((_B).first + (_B).second)
#define BUFFER_AVAILABLE_SIZE(_B)       (BUFFER_SIZE - BUFFER_GET_SIZE(_B))


// Package
#define PACKAGE_HEADER_SIZE             (4)
#define PACKAGE_BIDY_SIZE(_PH)          (19)


// session closed exception
class SessionClosed : std::exception {
    public:
        explicit SessionClosed() noexcept = default;
};


#endif // __SHADOWSOCKS_TYPES_INCLUDED__
