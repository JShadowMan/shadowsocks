#include <cstdio>
#include <iostream>
#include <fstream>
#include "shadowsocks/ss_logger.h"

/* static member initializing */
Ss_Logger Ss_Logger::_logger = Ss_Logger();


/* only debug mode */
void Ss_Logger::debug(const std::string &message) {
#ifdef DEBUG_MODE
    std::cout << message << std::endl;
#endif
}
