#ifndef __SHADOWSOCKS_SELECTOR_INCLUDED__
#define __SHADOWSOCKS_SELECTOR_INCLUDED__
#pragma once


// shadowsocks headers
#include "shadowsocks/ss_types.h"


/* `Ss_Selector` class */
class Ss_Selector {
    public:
        enum class SelectorEvent: int8_t {
            SE_READABLE = SELECTOR_EVENT_IN,
            SE_WRITABLE = SELECTOR_EVENT_OUT
        };

    public:
        using SelectorCallback = std::function<
            void(SOCKET, Ss_Selector::SelectorEvent)
        >;

    private:
        using SelectorEvents = std::initializer_list<SelectorEvent>;

    public:
        void registerSocket(SOCKET s, SelectorEvents events);
        void deleteSocket(SOCKET s);
        void select();

    public:
        explicit Ss_Selector(SelectorCallback &&cb);
        ~Ss_Selector() = default;

    private:
        std::function<void(SOCKET, SelectorEvent)> _callback;
        std::map<SELECTOR_KEY, SELECTOR_VALUE> _sockets;
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
