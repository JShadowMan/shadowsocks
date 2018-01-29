#include <string>
#include <cstdlib>
#include <cstring>
#include "shadowsocks/ss_core.h"


void Ss_Core::check_version() {
    if (std::strcmp(module_version, UNKNOWN_MODULE_VERSION_ERROR) == 0) {
        /**
         * \todo logger
         */
        std::exit(SHADOWSOCKS_MODULE_INVALID_CODE);
    }
}
