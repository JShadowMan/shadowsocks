#ifndef __SHADOWSOCKS_SERVER_INCLUDED__
#define __SHADOWSOCKS_SERVER_INCLUDED__

/* shadowsocks-module information */
#define MODULE_NAME "shadowsocks-server"
#define MODULE_VERSION "0.0.1"
#define PID_FILE "/var/shadowsocks/ss-server.pid"


/* daemon service */
#include "shadowsocks/ss_config.h"
#include "shadowsocks/ss_daemon.h"


/* shadowsocks-server service */
class Ss_Server : Ss_Daemon {
    public:
        explicit Ss_Server(Ss_Config &config): Ss_Daemon(config) {}

    public:
        void run_forever() final;

    private:
        Ss_Config _config;
};


#endif  // __SHADOWSOCKS_SERVER_INCLUDED__
