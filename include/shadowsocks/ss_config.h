#ifndef __SHADOWSOCKS_CONFIG_INCLUDED__
#define __SHADOWSOCKS_CONFIG_INCLUDED__

#include <map>
#include <string>


class Ss_Config {
    public:
        Ss_Config(int argc, char *argv[]);

    private:
        using ArgsMap = std::map<std::string, std::string>;

    private:
        ArgsMap *parse_args(int argc, char *argv[]);
};



#endif  // __SHADOWSOCKS_CONFIG_INCLUDED__