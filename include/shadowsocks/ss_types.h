#ifndef __SHADOWSOCKS_TYPES_INCLUDED__
#define __SHADOWSOCKS_TYPES_INCLUDED__


// config by auto generated
#include "ss_config.h"


// standard headers
#include <map>
#include <list>
#include <ctime>
#include <tuple>
#include <cstdio>
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
#include <forward_list>
#include <initializer_list>


// platform headers
#if defined(__platform_linux__)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <poll.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#elif defined(__platform_windows__)
#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif


#define OPERATOR_SUCCESS                (0)
#define OPERATOR_FAILURE                (-1)


#endif // __SHADOWSOCKS_TYPES_INCLUDED__
