#ifndef __SHADOWSOCKS_DAEMON_INCLUDED__
#define __SHADOWSOCKS_DAEMON_INCLUDED__


/**
 * Class: SsDaemon
 *
 *
 */
class SsDaemon {
    public:
        static void startDaemon();

    private:
        static bool createPidFile(const char *pidFile, int pid);
};


#endif // __SHADOWSOCKS_DAEMON_INCLUDED__
