#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_daemon.h"


/* static methods in daemon */
static void signalHandler(int signum);


// shadowsocks header
void SsCore::printShadowsocksHeader(std::ostream &out) {
#ifndef __debug__
    out << "Shadowsocks-" << SHADOWSOCKS_MODULE << " "
        << "VERSION: " << SHADOWSOCKS_VERSION << std::endl
        << "Copyright (C) 2018 Jayson Wang <jayson@shellboot.com>" << std::endl
        << "MIT License: " << "<" << SHADOWSOCKS_LICENSE_LINK << ">"
        << std::endl << std::endl;


#endif


    // do nothing on debug mode
}

// initializing environments
void SsCore::initShadowsocksEnvironments() {
    printShadowsocksHeader(std::cout);

    initDefaultLogger();
    initSocketEnvironments();
    catchSignal();
}

// logger initializing
void SsCore::initDefaultLogger() {
    auto logger = new SsLogger(std::cout);

#ifdef __debug__
    logger->setLevel(SsLogger::LoggerLevel::LL_DEBUG);


#endif


    // add default logger to global
    SsLogger::addLogger("stdout", logger);
    SsLogger::verbose("create logger `stdout` and activate it");
}

// initializing socket
void SsCore::initSocketEnvironments() {
#ifdef __windows__
    WSAData winSocket{};
    if (WSAStartup(MAKEWORD(2, 2), &winSocket) == OPERATOR_FAILURE) {
        SsLogger::emergency("socket startup error occurs on windows");
    }
    SsLogger::verbose("socket startup success on windows");


#endif


    // do nothing other platform
    SsLogger::debug("socket environment initialized");
}

// shutdown shadowsocks
void SsCore::shutdownShadowSocks(int state) {
    SsLogger::info("shadowsocks shutdown with state = %d", state);
    std::exit(state);
}

// catch signal
void SsCore::catchSignal() {
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        SsLogger::emergency("cannot catch SIGINT");
    }
    SsLogger::verbose("signal catch SIGINT");

    if (signal(SIGTERM, signalHandler) == SIG_ERR) {
        SsLogger::emergency("cannot catch SIGTERM");
    }
    SsLogger::verbose("signal catch SIGTERM");

#ifdef SIGQUIT
    if (signal(SIGQUIT, signalHandler) == SIG_ERR) {
        SsLogger::emergency("cannot catch SIGQUIT");
    }
    SsLogger::verbose("signal catch SIGQUIT");


#endif


    SsLogger::debug("register signal handler to catch SIGINT and SIGTERM");
}

// start daemon when debug mode disabled and on posix platform
void SsCore::startDaemon() {
#ifndef __debug__
#ifdef __linux__
    SsDaemon::startDaemon();


#endif


#endif
}


/* static methods definition */
void signalHandler(int signum) {
    SsLogger::debug("receive signal, signum = %d", signum);

    if (signum == SIGTERM) {
        SsCore::shutdownShadowSocks(OPERATOR_SUCCESS);
    }

#ifdef SIGQUIT
    if (signum == SIGQUIT) {
        SsCore::shutdownShadowSocks(OPERATOR_SUCCESS);
    }


#endif

    SsCore::shutdownShadowSocks(OPERATOR_FAILURE);
}


// ShadowsocksError constructor
template <typename ...Args>
ShadowsocksError<Args...>::ShadowsocksError(SsLogger::LoggerLevel level,
                                            const char *fmt, Args... args) {
    _message = SsLogger::log(level, fmt, args...);
}
