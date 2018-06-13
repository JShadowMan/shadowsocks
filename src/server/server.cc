#include <iostream>
#include <cstdlib>
#include "ss_config.h"


void atExitHandler() {
    std::cout << "atExitHandler" << std::endl << std::flush;
}


int main(int argc, char *argv[]) {
    std::cout << APPLICATION_NAME << std::endl;

    std::cout << std::atexit(atExitHandler);

    return 0;
}
