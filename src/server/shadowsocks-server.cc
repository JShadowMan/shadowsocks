/* shadowsocks-core header */
#include "shadowsocks/ss_core.h"


/* shadowsocks-server main entry-point */
int main(int argc, char *argv[]) {
    // check build environment
    Ss_Core::check_version();

    // instance new Ss_Config object
    Ss_Config config = Ss_Config();

    // instance shadowsocks-server
    Ss_Server server = Ss_Server(config);

    // start server
    server.run_forever();

    // success exit
    return 0;
}
