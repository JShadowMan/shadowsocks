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


class SsSelectorObject;


class SsSelector {
    public:
        enum class SelectorEvent : uint8_t {
            SE_READABLE = SELECTOR_EVENT_IN,
            SE_WRITABLE = SELECTOR_EVENT_OUT
        };
        using SelectorEvents = std::initializer_list<SelectorEvent>;
#if defined(__platform_linux__)
        using Descriptor = int;
#elif defined(__platform_windows__)
        using Descriptor = SOCKET;
#endif
        using SelectResult = std::vector<std::pair<Descriptor, SelectorEvent>>;

    public:
        SsSelector();
        void add(Descriptor descriptor, SelectorEvents events);
        void remove(Descriptor descriptor);
        void movify(Descriptor descriptor, SelectorEvents events);
        SelectResult select(int timeout);

    private:
#if defined(__platform_linux__)
        using SelectObject = int;
#elif defined(__platform_windows__)
        using SelectObject = int;
#endif

    private:
        std::map<SsSelector::Descriptor, SsSelectorObject> _objects;
};


class SsSelectorObject {
    public:
        SsSelectorObject(SsSelector::SelectorEvents events);
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
