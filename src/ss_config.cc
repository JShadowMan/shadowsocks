#include <iostream>
#include "shadowsocks/ss_config.h"


/* Methods of Ss_Config */
Ss_Config::Ss_Config(std::string &config) {
}

bool Ss_Config::is_server_config() {
    return true;
}

bool Ss_Config::is_client_config() {
    return !is_server_config();
}