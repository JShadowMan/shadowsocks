#include <iostream>
#include "shadowsocks/ss_core.h"


/* shadowsocks-server commands */
struct option module_long_options[] = {
/*        name                has_arg           flag      val*/
    { "server-port",     required_argument,    nullptr,    0 },
    { "server-address",  required_argument,    nullptr,    0 },
    { "password",        required_argument,    nullptr,    0 },
    { nullptr,           no_argument,          nullptr,    0 }
};


/* shadowsocks-server main entry-point */
int main(int argc, char *argv[]) {
    // check build environment
    Ss_Core::check_version();

    auto config = new Ss_Config(argc, argv);

    return 0;
}
