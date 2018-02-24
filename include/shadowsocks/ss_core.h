#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__

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

/* error definitions */
#define EXIT_SHADOWSOCKS_MODULE_INVALID 0xffff
#define ERROR_UNKNOWN_MODULE_VERSION "unknown"

/* other some definition */
#define FORMAT_PLACEHOLDER ('?')

/* Class Ss_Core */
class Ss_Core {
    public:
        static void check_version();

    public:
        static void trigger_error(int error_code, std::string &error);

    public:
        constexpr static const char *module_name = MODULE_NAME;
        constexpr static const char *module_version = MODULE_VERSION;
        constexpr static const char *pid_file = PID_FILE;
        constexpr static const char *time_format = "%d-%m-%Y %I:%M:%S";
};


#endif  // __SHADOWSOCKS_CORE_INCLUDED__
