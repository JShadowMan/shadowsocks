#ifndef __SHADOWSOCKS_LOGGER_INCLUDED__
#define __SHADOWSOCKS_LOGGER_INCLUDED__


class Ss_Logger {
    public:
        using Ss_LoggerType = int;

    public:
        Ss_Logger() = default;
        explicit Ss_Logger(Ss_LoggerType type);

    private:
        Ss_LoggerType type = SS_LOGGER_CONSOLE_TYPE | SS_LOGGER_FILE_TYPE;

    public:
        constexpr static int SS_LOGGER_FILE_TYPE = 0x0001;
        constexpr static int SS_LOGGER_CONSOLE_TYPE = 0x0002;
};



#endif
