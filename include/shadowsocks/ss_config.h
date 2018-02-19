#ifndef __SHADOWSOCKS_CONFIG_INCLUDED__
#define __SHADOWSOCKS_CONFIG_INCLUDED__

/* standard library */
#include <map>


/* Class Ss_Config */
class Ss_Config {
    public:
        Ss_Config() = default;

    private:
        using ArgsMap = std::map<std::string, std::string>;

    private:
        ArgsMap _config;
};



#endif  // __SHADOWSOCKS_CONFIG_INCLUDED__