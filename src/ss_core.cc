#include <iostream>
#include "shadowsocks/ss_core.h"

/* initializing Ss_Core static member */
Ss_Config *Ss_Core::config = nullptr;
Ss_Logger *Ss_Core::logger = nullptr;


/* methods of Ss_Core */
Ss_Config *Ss_Core::parse_args(int argc, char *argv[]) {
    auto config = new Ss_Config();

    return config;
}

void Ss_Core::start_server() {
    std::cout << "Server start ..." << std::endl;
}

void Ss_Core::set_config(Ss_Config *config) {
    Ss_Core::config = config;
}

Ss_Config *Ss_Core::get_config() {
    return config;
}

void Ss_Core::set_logger(Ss_Logger *logger) {
    Ss_Core::logger = logger;
}

Ss_Logger *Ss_Core::get_logger() {
    return logger;
}
