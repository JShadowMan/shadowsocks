#include <iostream>
#include "shadowsocks/ss_core.h"


int main(int argc, char *argv[]) {
    std::cout << "Client Version: " << Ss_Core::module_version << std::endl;
}
