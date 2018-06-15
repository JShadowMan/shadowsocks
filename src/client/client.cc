#include "shadowsocks/ss_core.h"


int main(int argc, char *argv[]) {
    SsCore::enableDebugLogger(SsLogger::LoggerLevel::LL_DEBUG);
    SsCore::initEnvironments();

    return 0;
}
