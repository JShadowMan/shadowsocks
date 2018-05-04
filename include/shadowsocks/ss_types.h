#ifndef __SHADOWSOCKS_TYPES_INCLUDED__
#define __SHADOWSOCKS_TYPES_INCLUDED__
#pragma once


// types definition
#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/epoll.h>

#define SOCKET          int


#elif __windows__
#include <Windows.h>
#include <WinSock2.h>
#define SOCKET          SOCKET


#endif /* socket headers end */


// socket error flag
#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)


#endif /* socket error flag end */


// success flag
#define OPERATOR_SUCCESS 0


// callback flag
#define SELECTOR_CALLBACK        public


#endif // __SHADOWSOCKS_TYPES_INCLUDED__
