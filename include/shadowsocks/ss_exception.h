#ifndef __SHADOWSOCKS_EXCEPTION_INCLUDED__
#define __SHADOWSOCKS_EXCEPTION_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_logger.h"


class SsException : public std::runtime_error {
    public:
        SsException(SsLogger::LoggerLevel level, std::string message);
        SsException(SsLogger::LoggerLevel level, std::string &&message);
};


#endif // __SHADOWSOCKS_EXCEPTION_INCLUDED__
