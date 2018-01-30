#include <string>
#include <cstdlib>
#include <cstring>
#include "shadowsocks/ss_core.h"


/**
 * check version of shadowsocks-server/client
 */
void Ss_Core::check_version() {
    if (std::strcmp(module_version, ERROR_UNKNOWN_MODULE_VERSION) == 0) {
        /**
         * \todo logger
         */
        std::exit(EXIT_SHADOWSOCKS_MODULE_INVALID);
    }
}
