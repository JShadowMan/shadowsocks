#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__
#pragma once

// check and definition shadowsocks version
#include <fstream>

#ifndef SHADOWSOCKS_VERSION
#   define SHADOWSOCKS_VERSION "UNKNOWN"
#endif

// check and definition shadowsocks module
#ifndef SHADOWSOCKS_MODULE
#   define SHADOWSOCKS_MODULE "UNKNOWN"
#endif

// MIT License link
#define SHADOWSOCKS_LICENSE_LINK \
    "https://raw.githubusercontent.com/JShadowMan/shadowsocks/master/LICENSE"


/* `Ss_Core` class */
class Ss_Core {
    public:
        static std::ostream &printShadowSocksHeader(std::ostream &s);
        static std::string &&getLastError();
        static void printLastError(std::string &additionalMessage);
        static void printLastError(const char *additionalMessage);
};


#endif // __SHADOWSOCKS_CORE_INCLUDED__
