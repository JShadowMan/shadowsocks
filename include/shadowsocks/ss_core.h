#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__


// shadowsocks types definitions
#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_logger.h"


/**
 * Class: SsCore
 *
 *
 */
class SsCore {
    public:
        static void initShadowsocksEnvironments();
        static void shutdownShadowSocks(int state = OPERATOR_FAILURE);
        static void startDaemon();

    private:
        static void printShadowsocksHeader(std::ostream &out);
        static void initDefaultLogger();
        static void initSocketEnvironments();
        static void catchSignal();
};


/**
 * Exception: ShadowsocksError
 *
 * @todo: fix it
 */
template <typename ...Args>
class ShadowsocksError : std::exception {
    public:
        explicit ShadowsocksError(SsLogger::LoggerLevel level,
                                  const char *fmt, Args ...args);

    public:
        inline const char *what() const noexcept final {
            return _message.c_str();
        }

    private:
        std::string _message;
};


#endif // __SHADOWSOCKS_CORE_INCLUDED__
