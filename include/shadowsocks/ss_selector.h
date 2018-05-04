#ifndef __SHADOWSOCKS_SELECTOR_INCLUDED__
#define __SHADOWSOCKS_SELECTOR_INCLUDED__
#pragma once


// standard libraries
#include <map>
#include <list>
#include <cstdint>
#include <functional>
#include <initializer_list>


// shadowsocks headers
#include "shadowsocks/ss_types.h"


/* `Ss_Selector` class */
class Ss_Selector {
    public:
        enum class SelectorEvent: int8_t {
            SE_READABLE = 1,
            SE_WRITABLE = 2
        };

    public:
        using SelectorCallback = std::function<
            void(SOCKET, Ss_Selector::SelectorEvent)
        >;

    private:
        using SelectorEvents = std::initializer_list<SelectorEvent>;

    public:
        void registerSocket(SOCKET s, SelectorEvents events);
        void select();

    public:
        explicit Ss_Selector(SelectorCallback &cb);
        ~Ss_Selector() = default;

    private:
        std::function<void(SOCKET, SelectorEvent)> _callback;

#ifdef __linux__
    private:
        std::map<SOCKET, pollfd> _sockets;


#elif __windows__
    private:
        std::list<SOCKET> _readable;
        std::list<SOCKET> _writable;


#endif
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
