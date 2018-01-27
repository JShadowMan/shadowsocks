#ifndef __SHADOWSOCKS_SERVER_INCLUDED__
#define __SHADOWSOCKS_SERVER_INCLUDED__

#include "shadowsocks/ss_service.h"


class Ss_Server : Ss_Service {
    public:
        Ss_Server() = default;

    public:
        void run() final;
};


#endif
