#ifndef __SHADOWSOCKS_LOGGER_INCLUDED__
#define __SHADOWSOCKS_LOGGER_INCLUDED__


// shadowsocks types
#include "shadowsocks/ss_types.h"


/**
 * Class: SsLogger
 *
 *
 */
class SsLogger {
    public:
        enum class LoggerLevel : uint8_t {
            LL_VERBOSE      = 0x00,
            LL_DEBUG        = 0x10,
            LL_INFO         = 0x20,
            LL_WARNING      = 0x40,
            LL_ERROR        = 0x80,
            LL_EMERGENCY    = 0xff
        };

    public:
        using Format = const char *;
        using LoggerName = const char *;
        using SsLoggerPtr = std::shared_ptr<SsLogger>;

    public:
        explicit SsLogger(std::ostream &out);

    public:
        void setLevel(LoggerLevel level);

    public:
        static void addLogger(LoggerName name, SsLogger *logger);

    public:
        template <typename ...Args>
        static void info(Format fmt, Args ...args);

        template <typename ...Args>
        static void emergency(Format fmt, Args ...args);

    private:
        static void log(LoggerLevel level, std::string &&message);

        template <typename ...Args>
        static std::string format(int fmtStart, Args ...args);


    private:
        std::ostream &_output;
        std::string _format = LOGGER_DEFAULT_FORMAT;
        LoggerLevel _level = LoggerLevel::LL_INFO;

    private:
        static std::map<SsLogger::LoggerName, SsLogger::SsLoggerPtr> _loggers;
};


// interesting events.
template<typename ...Args>
void SsLogger::info(SsLogger::Format fmt, Args... args) {
    log(LoggerLevel::LL_INFO, format(0, args...));
}

// system is unusable, will be exit
template<typename ...Args>
void SsLogger::emergency(SsLogger::Format fmt, Args... args) {
//    SsFormatter formatter(fmt);
//    log(LoggerLevel::LL_EMERGENCY, formatter(args...));
}

// format parameters and output it
template<typename ...Args>
std::string SsLogger::format(int fmtStart, Args... args) {
    return std::__cxx11::string();
}


#endif // __SHADOWSOCKS_LOGGER_INCLUDED__
