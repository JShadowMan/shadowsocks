#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__

/* error definitions */
#define EXIT_SHADOWSOCKS_MODULE_INVALID 0x0001
#define ERROR_UNKNOWN_MODULE_VERSION "unknown"

#define EXIT_FORMAT_NOT_MATCHED 0x1001
#define ERROR_FORMAT_NOT_MATCHED "Format string invalid '?'"

#define EXIT_INVALID_OPTION 0x0002
#define ERROR_INVALID_OPTION "Invalid option '?'"


/* other definitions */
#define FORMAT_PLACEHOLDER_FLAG ('?')

/* other standard headers */
#include <string>
#include <initializer_list>

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
#include "shadowsocks/ss_utils.h"


/* Class Ss_Core */
class Ss_Core {
    public:
        static void check_version();

    public:
        static void trigger_error(int error_code, std::string &error);

    public:
        constexpr static const char *module_name = MODULE_NAME;
        constexpr static const char *module_version = MODULE_VERSION;
};


#endif  // __SHADOWSOCKS_CORE_INCLUDED__
