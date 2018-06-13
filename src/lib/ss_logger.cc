#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"


#define LOGGER_TIME_INFO_SIZE               (128)


// static members definition
std::map<SsLogger::LoggerName, SsLogger::SsLoggerPtr> SsLogger::_loggers{};


// SsLogger constructor
SsLogger::SsLogger(std::ostream &out) : _output(out) {
    // empty constructor
}

// SsLogger destructor
SsLogger::~SsLogger() {
    SsLogger::debug("%s closed", this);
}

// add logger to global
void SsLogger::addLogger(SsLogger::LoggerName name, SsLoggerPtr logger) {
    logger->setName(name);
    _loggers[name] = std::move(logger);
}

// remove logger by name
bool SsLogger::removeLogger(SsLogger::LoggerName name) {
    if (_loggers.find(name) == _loggers.end()) {
        return false;
    }

    _loggers.erase(name);
    return true;
}

// remove all logger
void SsLogger::cleanupLogger() {
    _loggers.clear();
}

// set level of logger
void SsLogger::setLevel(LoggerLevel level) {
    _level = level;
}

// named logger
void SsLogger::setName(SsLogger::LoggerName name) {
    _name = name;
}

// do output message when level correct
void SsLogger::log(LoggerLevel level, std::string message) {
    if (_loggers.empty()) {
        return;
    }

    for (auto &pair : _loggers) {
        auto &logger = pair.second;
        if (level >= logger->_level) {
            logger->_output
                << level << ": "
                << currentDate(logger->_dateFormat.c_str())
                << message
                << std::endl;
        }
    }
}

// format current time
std::string SsLogger::currentDate(SsLogger::Format fmt) {
    time_t rawTime;
    std::time(&rawTime);

    static auto buffer = new char[LOGGER_TIME_INFO_SIZE];
    std::strftime(buffer, LOGGER_TIME_INFO_SIZE, fmt, std::localtime(&rawTime));

    return buffer;
}

// output logger
std::ostream &operator<<(std::ostream &out, SsLogger *logger) {
    out << "SsLogger["
        << "name=" << logger->_name
        << "]";

    return out;
}

// output level text
std::ostream &operator<<(std::ostream &out, const SsLogger::LoggerLevel &level) {
    switch (level) {
        case SsLogger::LoggerLevel::LL_VERBOSE:     out << "VERBOSE";   break;
        case SsLogger::LoggerLevel::LL_DEBUG:       out << "DEBUG";     break;
        case SsLogger::LoggerLevel::LL_INFO:        out << "INFO";      break;
        case SsLogger::LoggerLevel::LL_WARNING:     out << "WARNING";   break;
        case SsLogger::LoggerLevel::LL_ERROR:       out << "ERROR";     break;
        case SsLogger::LoggerLevel::LL_EMERGENCY:   out << "EMERGENCY"; break;
    }

    return out;
}

// TupleElementPrinter constructor
TupleElementPrinter::TupleElementPrinter(std::ostream &out) :
    _output(out), _defaultFlags(_output.flags()) {
}

// temporarily set a flags to stream
void TupleElementPrinter::setFlag(std::ios::fmtflags flags) {
    _defaultFlags = _output.setf(flags, std::ios::basefield);
}
