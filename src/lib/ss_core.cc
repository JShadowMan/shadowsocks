#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"


// initializing environments
void SsCore::initShadowSocksEnvironments() {
    initSocketEnvironments();
}

// initializing socket
void SsCore::initSocketEnvironments() {
#ifdef __windows__
    WSAData winSocket{};
    if (WSAStartup(MAKEWORD(2, 2), &winSocket) == OPERATOR_FAILURE) {
        SsLogger::emergency("socket startup error occurs on windows");
    }


#endif
    // do nothing other platform

    SsLogger::info("socket environment initialized, %d, %s, %f, %x", 1, "aa", 0.23, 1024);
}

// shutdown shadowsocks
void SsCore::shutdownShadowSocks(int state) {
    std::exit(state);
}
