#include "shadowsocks/ss_core.h"


/* shadowsocks-server commands */
const struct option module_long_options[] = {
    GETOPT_DEF_SERVER_ADDRESS,  // server-address
    GETOPT_DEF_SERVER_PORT,  // server-port
    GETOPT_DEF_PASSWORD,  // password
    GETOPT_DEF_DAEMON,  // daemon
    GETOPT_DEF_METHOD,  // method
    GETOPT_DEF_END  // end of long options
};
/** Short options
 *
 *  start-character return when lost arguments
 *    c   no_argument
 *    c:  required_argument   eg. -c1, -c 1
 *    c:: optional_argument
 */
const char *module_short_options = ":s:p:P:";


/* shadowsocks-server main entry-point */
int main(int argc, char *argv[]) {
    // check build environment
    Ss_Core::check_version();

    // parse argument configure
    Ss_Config config = Ss_Config(argc, argv);

    return 0;
}
