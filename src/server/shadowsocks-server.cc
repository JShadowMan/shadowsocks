#include <iostream>
#include "shadowsocks/ss_core.h"


int main(int argc, char *argv[]) {
    // check build environment
    Ss_Core::check_version();

    std::cout << "Server Version: " << Ss_Core::module_version << std::endl;
    return 0;
}
