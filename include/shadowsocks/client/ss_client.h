#ifndef __SHADOWSOCKS_CLIENT_INCLUDED__
#define __SHADOWSOCKS_CLIENT_INCLUDED__

/* shadowsocks-module information */
#define MODULE_NAME "shadowsocks-client"
#define MODULE_VERSION "0.0.1"
#define PID_FILE "/var/shadowsocks/ss-client.pid"


/* daemon service */
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_daemon.h"
#include "shadowsocks/ss_config.h"


/* shadowsocks-client service */
class Ss_Client : Ss_Daemon {
    public:
        explicit Ss_Client(Ss_Config &config): Ss_Daemon(config) {}

    public:
        void run_forever() final;
};




#endif  // __SHADOWSOCKS_CLIENT_INCLUDED__
