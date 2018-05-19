#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"


// static members definition
std::map<SsLogger::LoggerName, SsLogger::SsLoggerPtr> SsLogger::_loggers{};


// SsLogger constructor
SsLogger::SsLogger(std::ostream &out) : _output(out) {
    // empty constructor
}

// add logger to global
void SsLogger::addLogger(SsLogger::LoggerName name, SsLogger *logger) {
    _loggers[name] = std::make_shared<SsLogger>(*logger);
}

// set level of logger
void SsLogger::setLevel(LoggerLevel level) {
    _level = level;
}

// do output message when level correct
void SsLogger::log(LoggerLevel level, std::string &&message) {
    for (auto &pair : _loggers) {
        auto &logger = pair.second;
        if (level >= logger->_level) {
            logger->_output << message;
        }
    }
}
