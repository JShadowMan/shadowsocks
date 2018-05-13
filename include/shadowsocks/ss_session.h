#ifndef __SHADOWSOCKS_SESSION_INCLUDED__
#define __SHADOWSOCKS_SESSION_INCLUDED__
#pragma once


// other shadowsocks headers
#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_package.h"


/* `Ss_Session` class */
class Ss_Session {
    public:
        Ss_Session() = default;
        ~Ss_Session();
        explicit Ss_Session(SOCKET s);

    SESSION_CALLBACK:
        void readableHandle();
        void writableHandle();

    private:
        SOCKET _clientSocket{};
        Ss_Package _package;
};


#endif // __SHADOWSOCKS_SESSION_INCLUDED__
