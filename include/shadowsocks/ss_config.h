#ifndef __SHADOWSOCKS_CONFIG_INCLUDED__
#define __SHADOWSOCKS_CONFIG_INCLUDED__

#include <string>
#include <map>


class Ss_Config {
    public:
        Ss_Config() = default;
        explicit Ss_Config(std::string &config);

    public:
        bool is_server_config();
        bool is_client_config();
};


#endif
