#include <sstream>

/* shadowsocks other headers */
#include "shadowsocks/ss_logger.h"

/* Ss_Logger macro */
#define DARK_GRAY       "\033[1;30m"
#define DEFAULT_COLOR   ""
#define LIGHT_YELLOW    "\033[1;33m"
#define LIGHT_RED       "\033[1;31m"
#define CLEAN_COLOR     "\033[0m"

/* static member initializing */
Ss_Logger Ss_Logger::_logger = Ss_Logger();


/* output message to logger/console */
void Ss_Logger::log(LoggerLevel level, std::string &message) {
    std::ostringstream buffer;

    /* color setting */
    switch (level) {
        case DEBUG_LEVEL:
            buffer << DARK_GRAY;
            break;
        case WARNING_LEVEL:
            buffer << LIGHT_YELLOW;
            break;
        case ERROR_LEVEL:
            buffer << LIGHT_RED;
            break;
        case INFO_LEVEL:
        default:
            buffer << DEFAULT_COLOR;
    }

    /* logger header */
    buffer << *Ss_Utils::current_time(Ss_Core::time_format) << "\t\u279c ";

    /* message output */
    buffer << message;

    /* clean color */
    buffer << CLEAN_COLOR;

    /* output to stdout */
    std::cout << buffer.str() << std::endl;
}

/* overload for lvalue version */
void Ss_Logger::log(LoggerLevel level, std::string &&message) {
    std::string temp_message(message);
    log(level, temp_message);
}

/* empty args and directly return format parameter */
std::string* Ss_Logger::format_parse(Format format) {
    return new std::string(format);
}
