#ifndef __SHADOWSOCKS_LOGGER_INCLUDED__
#define __SHADOWSOCKS_LOGGER_INCLUDED__

/* variable argument headers */
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

/* shadowsocks other headers */
#include "shadowsocks/ss_utils.h"
#include "shadowsocks/ss_core.h"

/* enable debug mode */
#define DEBUG_MODE


/* Ss_Logger Class */
class Ss_Logger {
    public:
        using LoggerLevel = const int;
        enum {
            DEBUG_LEVEL = 0,
            INFO_LEVEL,
            WARNING_LEVEL,
            ERROR_LEVEL
        };

    private:
        using Format = const char *;

    public:
        template<typename ...Args>
        static void debug(const char *format, Args... args);

        template<typename ...Args>
        static void info(const char *format, Args... args);

        template<typename ...Args>
        static void warning(const char *format, Args... args);

        template<typename ...Args>
        static void error(const char *format, Args... args);

    private:
        static void log(LoggerLevel level, std::string &message);
        static void log(LoggerLevel level, std::string &&message);

    private:
        template<typename T, typename ...Args>
        static std::string *format_parse(Format format, T val, Args... args);
        template<typename T, typename ...Args>
        static std::string *format_parse(Format format, T *val, Args... args);
        static std::string *format_parse(Format format);

    private:
        Ss_Logger() = default;

    private:
        static Ss_Logger _logger;
};


/* debug only */
template<typename ...Args>
void Ss_Logger::debug(const char *format, Args... args) {
#ifdef DEBUG_MODE
    log(DEBUG_LEVEL, *format_parse(format, args...));
#endif
}

/* simple info logger*/
template<typename ...Args>
void Ss_Logger::info(const char *format, Args... args) {
    log(INFO_LEVEL, *format_parse(format, args...));
}

/* waning logger*/
template<typename ...Args>
void Ss_Logger::warning(const char *format, Args... args) {
    log(WARNING_LEVEL, *format_parse(format, args...));
}

/* error logger*/
template<typename ...Args>
void Ss_Logger::error(const char *format, Args... args) {
    log(WARNING_LEVEL, *format_parse(format, args...));
}

/* format message */
template<typename T, typename ...Args>
std::string *Ss_Logger::format_parse(Format format, T val, Args... args) {
    std::ostringstream buffer;

    /* process all character */
    for (auto ch = format; *ch != '\0'; ++ch) {
        if (*ch == FORMAT_PLACEHOLDER && *(ch - 1) != '\\') {
            buffer << val << *format_parse(ch + 1, args...);
            break;
        } else {
            buffer << *ch;
        }
    }

    auto result = new std::string(buffer.str());
    return result;
}

/* format message with current param is pointer */
template<typename T, typename ...Args>
std::string* Ss_Logger::format_parse(Format format, T *val, Args... args) {
    return Ss_Logger::format_parse(format, *val, args...);
}


#endif  // __SHADOWSOCKS_LOGGER_INCLUDED__
