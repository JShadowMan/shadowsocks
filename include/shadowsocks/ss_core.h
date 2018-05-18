#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__


// shadowsocks types definitions
#include "shadowsocks/ss_types.h"


/**
 * Class: SsCore
 *
 *
 */
class SsCore {
    public:
        static void initShadowSocksEnvironments();
        static void shutdownShadowSocks(int state = OPERATOR_FAILURE);

    private:
        static void initSocketEnvironments();
};


#endif // __SHADOWSOCKS_CORE_INCLUDED__
