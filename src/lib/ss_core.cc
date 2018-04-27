#include "shadowsocks/ss_core.h"


// print program information and license to screen
std::ostream& Ss_Core::printShadowSocksHeader(std::ostream &s) {
    s << "ShadowSocks-" << SHADOWSOCKS_MODULE << " "
      << "Ver: " << SHADOWSOCKS_VERSION << std::endl;
    s << "Copyright (C) 2018 Jayson Wang <jayson@shellboot.com>" << std::endl;
    s << "MIT License: " << "<" SHADOWSOCKS_LICENSE_LINK ">" << std::endl;
    s << std::endl;

    return s;
}
