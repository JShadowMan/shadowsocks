#ifndef __SHADOWSOCKS_CLIENT_INCLUDED__
#define __SHADOWSOCKS_CLIENT_INCLUDED__

#include "shadowsocks/ss_service.h"


class Ss_Client : Ss_Service {
    public:
        Ss_Client() = default;

    public:
        void run() final;
};


#endif // __SHADOWSOCKS_CLIENT_INCLUDED__

