#ifndef __SHADOWSOCKS_DAEMON_INCLUDED__
#define __SHADOWSOCKS_DAEMON_INCLUDED__


class Ss_Daemon {
    public:
        Ss_Daemon() = default;

    public:
        virtual void run() = 0;
};


#endif // __SHADOWSOCKS_DAEMON_INCLUDED__
