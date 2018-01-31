#ifndef __SHADOWSOCKS_CONFIG_INCLUDED__
#define __SHADOWSOCKS_CONFIG_INCLUDED__


/* short name of arguments */
#define GETOPT_OPT_SERVER_ADDRESS ('s')
#define GETOPT_OPT_SERVER_PORT ('p')
#define GETOPT_OPT_PASSWORD ('P')
#define GETOPT_OPT_DAEMON ('d')
#define GETOPT_OPT_METHOD ('m')

/** getopt_long definitions
 *
 * name: name of the long options
 * has_arg: no_argument|required_argument|optional_argument
 * flag: specifies how results are returns are returned for a long options
 * val: is the value to return
 */
#define GETOPT_DEF_SERVER_ADDRESS   { "server-address", required_argument, nullptr, GETOPT_OPT_SERVER_ADDRESS }
#define GETOPT_DEF_SERVER_PORT      { "server-port",    required_argument, nullptr, GETOPT_OPT_SERVER_PORT }
#define GETOPT_DEF_PASSWORD         { "server-port",    required_argument, nullptr, GETOPT_OPT_PASSWORD }
#define GETOPT_DEF_DAEMON           { "daemon",         required_argument, nullptr, GETOPT_OPT_DAEMON }
#define GETOPT_DEF_METHOD           { "method",         required_argument, nullptr, GETOPT_OPT_METHOD }
#define GETOPT_DEF_END              { nullptr, no_argument, nullptr, 0 }


#include <map>
#include <string>

/* shadowsocks commands declaration */
extern const struct option module_long_options[];
extern const char *module_short_options;

/* Class Ss_Config */
class Ss_Config {
    public:
        Ss_Config(int argc, char *argv[]);

    private:
        using ArgsMap = std::map<std::string, std::string>;

    private:
        void parse_args(int argc, char *argv[]);

    private:
        ArgsMap _config;
};



#endif  // __SHADOWSOCKS_CONFIG_INCLUDED__