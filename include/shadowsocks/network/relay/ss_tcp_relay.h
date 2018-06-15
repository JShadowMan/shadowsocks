#ifndef __SHADOWSOCKS_TCP_RELAY_INCLUDED__
#define __SHADOWSOCKS_TCP_RELAY_INCLUDED__


#include "shadowsocks/ss_types.h"


class SsTcpRelay {
    public:
        template <typename Type>
        void before(std::function<void(std::vector<Type>)> callback);
        template <typename Type>
        void after(std::function<void(std::vector<Type>)> callback);
};


#endif // __SHADOWSOCKS_TCP_RELAY_INCLUDED__
