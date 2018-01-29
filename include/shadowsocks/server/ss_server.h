#ifndef __SHADOWSOCKS_SERVER_INCLUDED__
#define __SHADOWSOCKS_SERVER_INCLUDED__

#include <getopt.h>

#define MODULE_NAME "shadowsocks-server"
#define MODULE_VERSION "0.0.1"

#define MODULE_ARGS_SHORT_OPTS ""
struct option module_long_options[] = {
/*        name                has_arg           flag      val*/
    { "server-port",     required_argument,    nullptr,    0 },
    { "server-address",  required_argument,    nullptr,    0 },
    { "password",        required_argument,    nullptr,    0 },
    { nullptr,           no_argument,          nullptr,    0 }
};


#endif  // __SHADOWSOCKS_SERVER_INCLUDED__
