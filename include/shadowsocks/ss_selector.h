#ifndef __SHADOWSOCKS_SELECTOR_INCLUDED__
#define __SHADOWSOCKS_SELECTOR_INCLUDED__


#include "shadowsocks/ss_types.h"


#if defined(__platform_linux__)
#define SELECTOR_EVENT_IN               POLLIN
#define SELECTOR_EVENT_OUT              POLLOUT
#elif defined(__platform_windows__)
#define SELECTOR_EVENT_IN               1
#define SELECTOR_EVENT_OUT              2
#endif


class SsSelectorHandler;


class SsSelector {
    public:
        enum class SelectorEvent : uint8_t {
            SE_READABLE = SELECTOR_EVENT_IN,
            SE_WRITABLE = SELECTOR_EVENT_OUT
        };
        using HandlerPointer = std::shared_ptr<SsSelectorHandler>;
        using SelectorEvents = std::initializer_list<SelectorEvent>;
#if defined(__platform_linux__)
        using Descriptor = int;
#elif defined(__platform_windows__)
        using Descriptor = SOCKET;
#endif

    public:
        static void select(HandlerPointer handler, SelectorEvents events);
};


class SsSelectorHandler {
    public:
        virtual ~SsSelectorHandler() = default;
        virtual SsSelector::Descriptor getDescriptor() const {
            return INVALID_DESCRIPTOR;
        }
        virtual void eventCallback(SsSelector::SelectorEvent event) {}
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
