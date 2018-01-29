#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__

// error code
#define SHADOWSOCKS_MODULE_INVALID_CODE 1
#define UNKNOWN_MODULE_VERSION_ERROR "unknown"

# ifdef SHADOWSOCKS_SERVER_MODULE
#   include "shadowsocks/server/ss_server.h"
# else
#   ifdef SHADOWSOCKS_CLIENT_MODULE
#     include "shadowsocks/client/ss_client.h"
#   else
#     define MODULE_VERSION UNKNOWN_MODULE_VERSION_ERROR
#   endif  // SHADOWSOCKS_CLIENT_MODULE
# endif  // SHADOWSOCKS_SERVER_MODULE


class Ss_Core {
    public:
        static void check_version();

    public:
        constexpr static const char *module_name = MODULE_NAME;
        constexpr static const char *module_version = MODULE_VERSION;
};


#endif  // __SHADOWSOCKS_CORE_INCLUDED__
