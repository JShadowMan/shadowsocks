#ifndef __SHADOWSOCKS_TYPES_INCLUDED__
#define __SHADOWSOCKS_TYPES_INCLUDED__


// standard headers
#include <map>
#include <list>
#include <ctime>
#include <tuple>
#include <memory>
#include <cassert>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <initializer_list>


// platform headers
#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <poll.h>


#elif __windows__
#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>


#endif


// platform types alias and definitions
#ifdef __linux__
#define SOCKET                          int
#define SELECTOR_KEY                    SOCKET
#define SELECTOR_VALUE                  pollfd
#define SELECTOR_EVENT_IN               POLLIN
#define SELECTOR_EVENT_OUT              POLLOUT

#define SELECTOR_VALUE_INIT(_S)         { .fd = (_S), .events = 0 }
#define SELECTOR_VALUE_ADD(_V, _E)      (_V).events |= (_E)


#elif __windows__
#define SOCKET                          SOCKET
#define SELECTOR_KEY                    SOCKET
#define SELECTOR_VALUE                  int
#define SELECTOR_EVENT_IN               1
#define SELECTOR_EVENT_OUT              2

#define SELECTOR_VALUE_INIT(_S)         (0)
#define SELECTOR_VALUE_ADD(_V, _E)      (_V) |= (_E)


#endif


// shadowsocks version definition
#ifndef SHADOWSOCKS_VERSION
#define SHADOWSOCKS_VERSION "UNKNOWN"


#endif

// shadowsocks module definition
#ifndef SHADOWSOCKS_MODULE
#define SHADOWSOCKS_MODULE "UNKNOWN"


#endif


// shadowsocks license link
#define SHADOWSOCKS_LICENSE_LINK \
    "https://raw.githubusercontent.com/JShadowMan/shadowsocks/master/LICENSE"


// operator flags
#define OPERATOR_SUCCESS                (0)
#define OPERATOR_FAILURE                (-1)


// socket error flag
#ifndef INVALID_SOCKET
#define INVALID_SOCKET                  OPERATOR_FAILURE


#endif


// session error flags
#ifdef __linux__
#elif __windows__
#define CONNECTION_RESET_BY_PEER       (10054)


#endif


// logger default format
#define LOGGER_DEFAULT_FORMAT           "%A %b %d %H:%M:%S %Y \t->\t "
#define LOGGER_TIME_INFO_SIZE           (128)


// network
using NetworkHost                       = const char *;
using NetworkPort                       = short;


#endif // __SHADOWSOCKS_TYPES_INCLUDED__
