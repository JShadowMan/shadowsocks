#include <iostream>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_config.h"

/* shadowsocks commands declaration */
extern struct option module_long_options[];


/**
 *
 * @param argc number of argument count
 * @param argv value of each arguments
 */
Ss_Config::Ss_Config(int argc, char *argv[]) {
    parse_args(argc, argv);
}

/**
 * @return stringify config
 */
std::string Ss_Config::operator<<() {
    std::string stringify_config();
}


/**
 *
 * @param argc
 * @param argv
 * @return
 */
void Ss_Config::parse_args(int argc, char *argv[]) {
//    auto args_map = new ArgsMap();
//
//    int option_index = 0;
//    int result = getopt_long(argc, argv,
//                             MODULE_ARGS_SHORT_OPTS,  ,
//                             &option_index);
//
//    return args_map;
}


