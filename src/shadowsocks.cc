#include "shadowsocks/ss_core.h"


int main(int argc, char *argv[]) {
    auto config = Ss_Core::parse_args(argc, argv);

    if (config->is_server_config()) {
        auto service = new Ss_Server();
        service->run();
    } else {
        auto service = new Ss_Client();
        service->run();
    }

    return 0;
}
