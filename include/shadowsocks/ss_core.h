#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__

/* error definitions */
#define EXIT_SHADOWSOCKS_MODULE_INVALID 0x0001
#define ERROR_UNKNOWN_MODULE_VERSION "unknown"

/* include server/client header */
# ifdef SHADOWSOCKS_SERVER_MODULE
#   include "shadowsocks/server/ss_server.h"
# else
#   ifdef SHADOWSOCKS_CLIENT_MODULE
#     include "shadowsocks/client/ss_client.h"
#   else
#     define MODULE_VERSION ERROR_UNKNOWN_MODULE_VERSION
#   endif  // SHADOWSOCKS_CLIENT_MODULE
# endif  // SHADOWSOCKS_SERVER_MODULE

/* other shadowsocks-headers */
#include "shadowsocks/ss_config.h"


class Ss_Core {
    public:
        static void check_version();

    public:
        constexpr static const char *module_name = MODULE_NAME;
        constexpr static const char *module_version = MODULE_VERSION;
};


#endif  // __SHADOWSOCKS_CORE_INCLUDED__
