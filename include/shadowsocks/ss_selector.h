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


class SsSelector {
    public:
        enum class SelectorEvent : uint8_t {
            SE_READABLE = SELECTOR_EVENT_IN,
            SE_WRITABLE = SELECTOR_EVENT_OUT
        };
        enum class SelectorState : uint8_t {
            SS_TIMEOUT = 0xff,
            SS_SUCCESS = 0x00,
            SS_FAILURE = 0x01
        };
        using SelectorEvents = std::initializer_list<SelectorEvent>;
#if defined(__platform_linux__)
        using Descriptor = int;
#elif defined(__platform_windows__)
        using Descriptor = SOCKET;
#endif
        using SelectResult = std::pair<
            SelectorState,
            std::vector<
                std::pair<Descriptor, std::tuple<bool, bool>>
            >
        >;

    public:
        SsSelector();
        ~SsSelector();
        void add(Descriptor descriptor, SelectorEvents events);
        void remove(Descriptor descriptor);
        void movify(Descriptor descriptor, SelectorEvents events);
        SelectResult select(int timeout);

    private:
        std::map<Descriptor, uint8_t> _objects;
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
