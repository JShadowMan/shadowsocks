#ifndef __SHADOWSOCKS_LOGGER_INCLUDED__
#define __SHADOWSOCKS_LOGGER_INCLUDED__


// shadowsocks types
#include "shadowsocks/ss_types.h"


/**
 * Class: SsFormatter
 *
 *
 */
class SsFormatter {
    public:
        using Format = const char *;

    public:
        explicit SsFormatter(Format fmt) : _format(fmt) {};

    public:
        std::string _format;

    public:
        template <typename Arg, typename ...Args>
        std::string operator()(Arg arg, Args... args);
        std::string operator()();
};



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
        using LoggerName = const char *;
        using SsLoggerPtr = std::shared_ptr<SsLogger>;

    public:
        explicit SsLogger(std::ostream &out);

    public:
        void setLevel(LoggerLevel level);

    public:
        static void addLogger(LoggerName name, SsLogger *logger);
        static void verbose(std::string &message);
        static void verbose(std::string &&message);
        static void debug(std::string &message);
        static void debug(std::string &&message);
        static void info(std::string &message);
        static void info(std::string &&message);
        static void warning(std::string &message);
        static void warning(std::string &&message);
        static void error(std::string &message);
        static void error(std::string &&message);

        static void emergency(std::string &message);
        static void emergency(std::string &&message);

    private:
        static void log(LoggerLevel level, std::string &message);

    private:
        std::ostream &_output;
        std::string _format = LOGGER_DEFAULT_FORMAT;
        LoggerLevel _level = LoggerLevel::LL_INFO;

    private:
        static std::map<SsLogger::LoggerName, SsLogger::SsLoggerPtr> _loggers;
};



// template methods definition
template<typename Arg, typename ...Args>
std::string SsFormatter::operator()(Arg arg, Args... args) {
    return "DEBUG MESSAGE";
}

#endif // __SHADOWSOCKS_LOGGER_INCLUDED__
