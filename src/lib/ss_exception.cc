#include "shadowsocks/ss_exception.h"


// SsException constructor
SsException::SsException(SsLogger::LoggerLevel level, std::string message):
    std::runtime_error(message) {
    SsLogger::log(level, message.c_str());
}

// SsException constructor
SsException::SsException(SsLogger::LoggerLevel level, std::string &&message):
    std::runtime_error(message) {
    SsLogger::log(level, what());
}
