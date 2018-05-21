#include "shadowsocks/ss_daemon.h"
#include "shadowsocks/ss_logger.h"


// program daemonize by double fork
void SsDaemon::startDaemon() {
#ifdef __linux__
    auto pid = fork();  // fork #1
    if (pid > 0) {
        SsLogger::debug("fork #1 parent exit, pid = %d", getpid());
        std::exit(OPERATOR_SUCCESS);
    }

    chdir("/");
    SsLogger::verbose("change program dir to /");

    setsid();
    SsLogger::verbose("creates a new session");

    umask(0);
    SsLogger::verbose("sets the calling process's file mode to 0");

    pid = fork();  // # fork #2
    if (pid > 0) {
        SsLogger::debug("fork #2 parent exit, pid = %d", getpid());
        std::exit(OPERATOR_SUCCESS);
    }

    SsLogger::debug("daemon has startup, pid = %d", getpid());


#elif __windows__
    SsLogger::warning("daemon mode is only supported on unix");


#endif
}

// create pid file
bool SsDaemon::createPidFile(const char *pidFile, int pid) {
    return false;
}
