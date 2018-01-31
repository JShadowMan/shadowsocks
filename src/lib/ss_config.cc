#include <iostream>
#include <getopt.h>
#include "shadowsocks/ss_core.h"

/* constant of Ss_Config */
#define GETOPT_PARSE_COMPLETE (-1)
#define GETOPT_NOT_MATCHED ('?')

/**
 *
 * @param argc number of argument count
 * @param argv value of each arguments
 */
Ss_Config::Ss_Config(int argc, char *argv[]) {
    parse_args(argc, argv);

    // check arguments
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
void Ss_Config::parse_args(int argc, char *argv[]) {
    int getopt_result = 0;
    int option_index = -1;

    /* print getopt error message */
    opterr = 0;

    while (true) {
        getopt_result = getopt_long(argc, argv,
                                    module_short_options, module_long_options,
                                    &option_index);

        /* parse complete */
        if (getopt_result == GETOPT_PARSE_COMPLETE) {
            break;
        }

        /* process all arguments */
        switch (getopt_result) {
            case GETOPT_OPT_SERVER_ADDRESS:{
                _config["server_address"] = optarg;
                break;
            }
            case GETOPT_OPT_SERVER_PORT:{
                _config["server_port"] = optarg;
                break;
            }
            case GETOPT_OPT_PASSWORD: {
                _config["password"] = optarg;
                break;
            }
            case GETOPT_OPT_DAEMON: {
                _config["daemon"] = optarg;
                break;
            }
            case GETOPT_NOT_MATCHED: {
                char *err = argv[optind];
                /* check is not single option character */
                if (optopt == 0) {
                    err = argv[optind - 1];
                } else {
                    /* check is `-x xxx` pattern */
                    if (err && err[0] != '-') {
                        err = argv[optind - 1];
                    }
                }

                auto error = Ss_Core::format(ERROR_INVALID_OPTION, {err});
                Ss_Core::trigger_error(EXIT_INVALID_OPTION, *error);
                break;
            }
            default:{
                std::cout << "default case" << std::endl;
            }
        }
    }

    for (auto pair : _config) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}
