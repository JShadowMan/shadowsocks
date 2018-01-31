#include <iostream>
#include <getopt.h>
#include "shadowsocks/ss_core.h"


/* shadowsocks-server commands */
const struct option module_long_options[] = {
/*        name                has_arg           flag      val*/
        {"server-address", required_argument, nullptr, 0},
        {"server-port",    required_argument, nullptr, 0},
        {"password",       required_argument, nullptr, 0},
        {nullptr,          no_argument,       nullptr, 0}
};
/** Short options
 *
 *  start-character return when lost arguments
 *    c   no_argument
 *    c:  required_argument   eg. -c1, -c 1
 *    c:: optional_argument
 */
const char *module_short_options = ":s:p:P:";

int main(int argc, char *argv[]) {
    std::cout << "Client Version: " << Ss_Core::module_version << std::endl;
}
