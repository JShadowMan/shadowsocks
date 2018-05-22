#ifndef __SHADOWSOCKS_SELECTOR_INCLUDED__
#define __SHADOWSOCKS_SELECTOR_INCLUDED__


#include "shadowsocks/ss_types.h"


/* class pre-declared */
class SsSelectorCallbackInterface;


/**
 * Class: SsSelector
 *
 *
 */
class SsSelector {
    public:
        enum class SelectorEvent: int8_t {
                SE_READABLE = SELECTOR_EVENT_IN,
                SE_WRITABLE = SELECTOR_EVENT_OUT
        };

        using SelectorCallback = std::function<
            void(SOCKET, SsSelector::SelectorEvent)
        >;

        using SelectorEvents = std::initializer_list<SelectorEvent>;

    public:
        SsSelector() = default;

    public:
        static void startEventLoop();
        static void select(SsSelectorCallbackInterface &cb,
                           SelectorEvents events);

    public:
        void doPoll();

    private:
        static std::shared_ptr<SsSelector> _instance;
        std::map<SELECTOR_KEY, SELECTOR_VALUE> _sockets;
};


/**
 * Interface: SsSelectorCallbackInterface
 *
 *
 */
class SsSelectorCallbackInterface {
    public:
        virtual void selectorCallback(SsSelector::SelectorEvent event) = 0;
};



#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
