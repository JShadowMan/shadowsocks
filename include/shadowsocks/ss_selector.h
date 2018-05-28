#ifndef __SHADOWSOCKS_SELECTOR_INCLUDED__
#define __SHADOWSOCKS_SELECTOR_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_logger.h"


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
        using SelectorEvents = std::initializer_list<SelectorEvent>;

    private:
        enum class SelectorResult : uint8_t {
            SR_TIMEOUT = 0xff,
            SR_SUCCESS = 0x00,
            SR_FAILURE = 0x01
        };
        using PollCollection = std::pair<SelectorResult, std::map<SOCKET, int>>;

    public:
        static void select(std::shared_ptr<SsSelectorCallbackInterface> cb,
                           SelectorEvents events);
        static void remove(SOCKET fd);

        static void startEventLoop();
        static void stopEventLoop();

    private:
        static PollCollection poll();
        static SelectorResult triggerHandler(PollCollection collection);

    private:
        static bool _eventLoopRunning;
        static std::map<SELECTOR_KEY, SELECTOR_VALUE> _events;
        static std::map<
            SELECTOR_KEY, std::shared_ptr<SsSelectorCallbackInterface>
        > _callbacks;
};


/**
 * Interface: SsSelectorCallbackInterface
 *
 *
 */
class SsSelectorCallbackInterface {
    public:
        virtual ~SsSelectorCallbackInterface() = default;

        virtual SOCKET getSocket() const {
            return 0;
        }

        virtual void selectorCallback(SsSelector::SelectorEvent event) {
            SsLogger::emergency("not implement selectorCallback method");
        }
};


#endif // __SHADOWSOCKS_SELECTOR_INCLUDED__
