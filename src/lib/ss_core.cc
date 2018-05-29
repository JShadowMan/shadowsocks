#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_daemon.h"


// static members initializing
std::vector<std::function<void(void)>> SsCore::_callbacks{};


/* static methods in daemon */
#ifdef __linux__
static void signalHandler(int signum);


#elif __windows__
static bool signalHandler(DWORD signum);


#endif


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
    for (auto &callback : _callbacks) {
        callback();
    }

    SsLogger::info("shadowsocks shutdown with state = %d", state);
    std::exit(state);
}

// catch signal
void SsCore::catchSignal() {
#ifdef __linux__
    auto handleSignal = [&] (int signum) {
        struct sigaction sig;
        sig.sa_handler = signalHandler;
        sigemptyset(&sig.sa_mask);
        sig.sa_flags = 0;

        sigaction(signum, &sig, nullptr);
        SsLogger::verbose("catch %d by sigaction", signum);
    };

    handleSignal(SIGINT);
    handleSignal(SIGTERM);
#ifdef SIGQUIT
    handleSignal(SIGQUIT);


#endif


#elif __windows__
    if (SetConsoleCtrlHandler((PHANDLER_ROUTINE) signalHandler, true)) {
        SsLogger::debug("the control handler is installed on windows");
    }


#endif


    // catch SIGINT and SIGTERM in linux / windows
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
#ifdef __linux__
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


#elif __windows__
bool signalHandler(DWORD signum) {
    switch (signum) {
        case CTRL_C_EVENT:
            SsCore::shutdownShadowSocks(OPERATOR_FAILURE);
            return true;
        case CTRL_CLOSE_EVENT:
            SsCore::shutdownShadowSocks(OPERATOR_SUCCESS);
            return true;
        default:
            SsLogger::debug("receive signal type = %d", signum);
            return false;
    }
}


#endif


// ShadowsocksError constructor
template <typename ...Args>
ShadowsocksError<Args...>::ShadowsocksError(SsLogger::LoggerLevel level,
                                            const char *fmt, Args... args) {
    _message = SsLogger::log(level, fmt, args...);
}

// on exit callback
void SsCore::atExit(std::function<void(void)> cb) {
    _callbacks.push_back(cb);
}
