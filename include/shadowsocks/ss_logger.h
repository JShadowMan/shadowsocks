#ifndef __SHADOWSOCKS_LOGGER_INCLUDED__
#define __SHADOWSOCKS_LOGGER_INCLUDED__

/* variable argument headers */
#include <string>

/* enable debug mode */
#define DEBUG_MODE


/* Ss_Logger Class */
class Ss_Logger {
    public:
        static void debug(const std::string &message);

    private:
        Ss_Logger() = default;

    private:
        static Ss_Logger _logger;
};


#endif  // __SHADOWSOCKS_LOGGER_INCLUDED__
