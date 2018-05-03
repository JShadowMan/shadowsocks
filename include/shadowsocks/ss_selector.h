#ifndef __SHADOWSOCKS_SELECTOR_INCLUDED__
#define __SHADOWSOCKS_SELECTOR_INCLUDED__
#pragma once


// standard libraries
#include <list>
#include <cstdint>
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

    private:
        using SelectorEvents = std::initializer_list<SelectorEvent>;

    public:
        void registerSocket(SOCKET s, SelectorEvents events);

    public:
        Ss_Selector() = default;
        ~Ss_Selector() = default;

    private:
        std::list<SOCKET> _readable;
        std::list<SOCKET> _writable;
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
