#ifndef __SHADOWSOCKS_CORE_INCLUDED__
#define __SHADOWSOCKS_CORE_INCLUDED__


#include "shadowsocks/ss_types.h"


class SsCore {
    public:
        static void initEnvironments();
        static void atExit(std::function<void()> callback);
        static void shutdownHandler();

    private:
        static void socketStartup();
        static void coreExitHandler();

    private:
        static std::vector<std::function<void()>> _exitCallbacks;
};


#endif // __SHADOWSOCKS_CORE_INCLUDED__
