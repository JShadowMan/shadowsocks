#ifndef __SHADOWSOCKS_SESSION_INCLUDED__
#define __SHADOWSOCKS_SESSION_INCLUDED__
#pragma once


// other shadowsocks headers
#include "shadowsocks/ss_types.h"


/* `Ss_Session` class */
class Ss_Session {
    public:
        Ss_Session() = default;
        explicit Ss_Session(SOCKET s);

    SESSION_CALLBACK:
        void readableHandle();
        void writableHandle();

    private:
        std::shared_ptr<u_char> peekBuffer(int length);
        bool bufferSizeGreatThan(int length);
        std::shared_ptr<u_char> fetchBuffer(int length);

    private:
        SOCKET _clientSocket;
};


#endif // __SHADOWSOCKS_SESSION_INCLUDED__
