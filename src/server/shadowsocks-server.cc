#include <iostream>
#include "shadowsocks/ss_core.h"


/* Ss_Server member methods */
void Ss_Server::run_forever() {
    std::cout << "Server running forever ..." << std::endl;
}


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
