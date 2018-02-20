#ifndef __SHADOWSOCKS_DAEMON_INCLUDED__
#define __SHADOWSOCKS_DAEMON_INCLUDED__

/* shadowsocks headers */
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_config.h"


/* Ss_Daemon Class */
class Ss_Daemon {
    public:
        explicit Ss_Daemon(Ss_Config &config): _config(config) {}

    public:
        virtual void run_forever();

    protected:
        Ss_Config _config;
};


#endif // __SHADOWSOCKS_DAEMON_INCLUDED__
