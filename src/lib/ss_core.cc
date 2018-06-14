#include "shadowsocks/ss_core.h"
#define DEBUG_LOGGER_NAME       ("debug")

// SsCore static members
std::vector<std::function<void()>> SsCore::_exitCallbacks;


// shadowsocks environment initializing
void SsCore::initEnvironments() {
    std::atexit(&SsCore::shutdownHandler);

    socketStartup();
}

// on internal error occurs, cleanup resources
void SsCore::shutdownHandler() {
    for (auto it = _exitCallbacks.rbegin(); it != _exitCallbacks.rend(); ++it) {
        (*it)();
    }
}

// register an cleanup handler to queue
void SsCore::atExit(std::function<void()> callback) {
    _exitCallbacks.emplace_back(callback);
}

// socket environment initializing on windows platform
void SsCore::socketStartup() {
#if defined(__platform_windows__)
    WSAData winSocketData{};
    if (WSAStartup(MAKEWORD(2, 2), &winSocketData) != OPERATOR_SUCCESS) {
        SsLogger::emergency("Socket environment startup failure on windows");
    }

    auto socketCleanup = [] () {
        if (WSACleanup() != OPERATOR_SUCCESS) {
            SsLogger::emergency("Socket environment cleanup failure");
        }
    };
    SsCore::atExit(socketCleanup);
    SsLogger::debug("Socket environment startup on windows");
#endif
}

// enable debug logger with stdout
void SsCore::enableDebugLogger(SsLogger::LoggerLevel level) {
    auto logger = std::make_shared<SsLogger>(std::cout);
#if defined(__type_debug__)
    logger->setLevel(level);
#endif

    SsLogger::addLogger(DEBUG_LOGGER_NAME, std::move(logger));
}

// disable debug logger
void SsCore::disableDebugLogger() {
    SsLogger::removeLogger(DEBUG_LOGGER_NAME);
}
