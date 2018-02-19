#include <iostream>
#include <cstdlib>
#include <cstring>
#include "shadowsocks/ss_core.h"


/* check version of shadowsocks-server/client */
void Ss_Core::check_version() {
    if (std::strcmp(module_version, ERROR_UNKNOWN_MODULE_VERSION) == 0) {
        /**
         * \todo logger
         */
        std::exit(EXIT_SHADOWSOCKS_MODULE_INVALID);
    }
}

/* trigger error handler and logging */
void Ss_Core::trigger_error(int error_code, std::string &error) {
    std::cerr << error << std::endl;
    std::exit(error_code);
}
