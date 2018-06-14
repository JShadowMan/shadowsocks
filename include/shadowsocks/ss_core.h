#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_logger.h"


class SsCore {
    public:
        static void initEnvironments();
        static void atExit(std::function<void()> callback);
        static void shutdownHandler();
        static void enableDebugLogger(SsLogger::LoggerLevel level);
        static void disableDebugLogger();

    private:
        static void socketStartup();

    private:
        static std::vector<std::function<void()>> _exitCallbacks;
};


#endif // __SHADOWSOCKS_CORE_INCLUDED__
