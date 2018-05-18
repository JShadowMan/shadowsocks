#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"


// static members definition
std::map<SsLogger::LoggerName, SsLogger::SsLoggerPtr> SsLogger::_loggers{};


// SsFormatter function
std::string SsFormatter::operator()() {
    return _format;
}

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

// verbose message
void SsLogger::verbose(std::string &message) {
    log(LoggerLevel::LL_VERBOSE, message);
}

// verbose message
void SsLogger::verbose(std::string &&message) {
    log(LoggerLevel::LL_VERBOSE, message);
}

// debug message
void SsLogger::debug(std::string &message) {
    log(LoggerLevel::LL_DEBUG, message);
}

// debug message
void SsLogger::debug(std::string &&message) {
    log(LoggerLevel::LL_DEBUG, message);
}

// info message
void SsLogger::info(std::string &message) {
    log(LoggerLevel::LL_INFO, message);
}

// info message
void SsLogger::info(std::string &&message) {
    log(LoggerLevel::LL_INFO, message);
}

// warning message
void SsLogger::warning(std::string &message) {
    log(LoggerLevel::LL_WARNING, message);
}

// warning message
void SsLogger::warning(std::string &&message) {
    log(LoggerLevel::LL_WARNING, message);
}

// error message
void SsLogger::error(std::string &message) {
    log(LoggerLevel::LL_ERROR, message);
}

// error message
void SsLogger::error(std::string &&message) {
    log(LoggerLevel::LL_ERROR, message);
}


// emergency message and exit
void SsLogger::emergency(std::string &message) {
    log(LoggerLevel::LL_EMERGENCY, message);
    SsCore::shutdownShadowSocks();
}

void SsLogger::emergency(std::string &&message) {
    log(LoggerLevel::LL_EMERGENCY, message);
    SsCore::shutdownShadowSocks();
}

// do output message when level correct
void SsLogger::log(LoggerLevel level, std::string &message) {
    if (_loggers.empty()) {
        SsLogger::addLogger("__default", new SsLogger(std::cout));
    }

    for (auto &pair : _loggers) {
        auto &logger = pair.second;
        if (level >= logger->_level) {
            logger->_output << message;
        }
    }
}
