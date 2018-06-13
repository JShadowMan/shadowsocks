#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"


int main(int argc, char *argv[]) {
    auto logger = std::make_shared<SsLogger>(std::cout);
#if defined(__type_debug__)
    logger->setLevel(SsLogger::LoggerLevel::LL_DEBUG);
#endif
    SsLogger::addLogger("stdout", logger);

    SsCore::initEnvironments();

    return 0;
}
