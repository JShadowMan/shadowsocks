#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_exception.h"


int main(int argc, char *argv[]) {
    SsCore::enableDebugLogger(SsLogger::LoggerLevel::LL_DEBUG);
    SsCore::initEnvironments();

    return 0;
}
