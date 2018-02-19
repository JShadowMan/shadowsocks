#include <iostream>
#include "shadowsocks/ss_core.h"


/* Ss_Server member methods */
void Ss_Client::run_forever() {
    std::cout << "Client running forever ..." << std::endl;
}


/* shadowsocks-client main entry-point */
int main(int argc, char *argv[]) {
    // check build environment
    Ss_Core::check_version();

    // instance new Ss_Config object
    Ss_Config config = Ss_Config();

    // instance shadowsocks-server
    Ss_Client client = Ss_Client(config);

    // start server
    client.run_forever();

    // success exit
    return 0;
}
