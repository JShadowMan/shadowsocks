#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"


// SsCore static members
std::vector<std::function<void()>> SsCore::_exitCallbacks;


// shadowsocks environment initializing
void SsCore::initEnvironments() {
    std::atexit(&SsCore::shutdownHandler);

    socketStartup();
    coreExitHandler();
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

    auto cleanupHandler = [] () {
        if (WSACleanup() != OPERATOR_SUCCESS) {
            SsLogger::emergency("Socket environment cleanup failure");
        }
    };
    SsCore::atExit(cleanupHandler);
    SsLogger::debug("Socket environment startup on windows");
#endif
}

// module exit callbacks
void SsCore::coreExitHandler() {
    atExit([] () {
        // logger cleanup
        SsLogger::cleanupLogger();
    });
}
