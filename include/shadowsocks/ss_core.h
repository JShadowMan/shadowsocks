#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__

#include "shadowsocks/ss_config.h"
#include "shadowsocks/ss_crypto.h"
#include "shadowsocks/ss_logger.h"
#include "shadowsocks/ss_service.h"
#include "shadowsocks/ss_server.h"
#include "shadowsocks/ss_client.h"


class Ss_Core {
    public:
        static Ss_Config *parse_args(int argc, char *argv[]);
        static void start_server();

    public:
        static void set_config(Ss_Config *config);
        static Ss_Config *get_config();

        static void set_logger(Ss_Logger *logger);
        static Ss_Logger *get_logger();

    private:
        static Ss_Config *config;
        static Ss_Logger *logger;
};


#endif
