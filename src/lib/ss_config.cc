#include <iostream>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_config.h"


Ss_Config::Ss_Config(int argc, char **argv) {

}

Ss_Config::ArgsMap* Ss_Config::parse_args(int argc, char **argv) {
    auto args_map = new std::map<std::string, std::string>;

    int option_index = 0;
    int result = getopt_long(argc, argv,
                             MODULE_ARGS_SHORT_OPTS, module_long_options,
                             &option_index);
}
