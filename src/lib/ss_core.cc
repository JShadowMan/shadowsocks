#include "shadowsocks/ss_core.h"


// initializing environments
void SsCore::initShadowSocksEnvironments() {

}

// initializing socket
void SsCore::initSocketEnvironments() {
#ifdef __windows__
    WSAData winSocket;
    if (WSAStartup(MAKEWORD(2, 2), &winSocket) == OPERATOR_FAILURE) {

    }


#endif
}