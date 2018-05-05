#ifndef __SHADOWSOCKS_TYPES_INCLUDED__
#define __SHADOWSOCKS_TYPES_INCLUDED__
#pragma once


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


// socket error flag
#ifndef SOCKET_ERROR
#define SOCKET_ERROR OPERATOR_FAILURE


#endif /* socket error flag end */


// operator flags
#define OPERATOR_SUCCESS                (0)
#define OPERATOR_FAILURE                (-1)


// callback flag
#define SELECTOR_CALLBACK        public


#endif // __SHADOWSOCKS_TYPES_INCLUDED__
