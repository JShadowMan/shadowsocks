#include "shadowsocks/ss_selector.h"
#include "shadowsocks/ss_logger.h"


// static members initializing
std::shared_ptr<SsSelector> SsSelector::_instance = nullptr;


// poll all socket descriptor
void SsSelector::startEventLoop() {
    SsLogger::info("event loop started");
}

// do poll all socket descriptor
void SsSelector::doPoll() {

}

// register a callback when socket available
void SsSelector::select(SsSelectorCallbackInterface &cb,
                        SsSelector::SelectorEvents events) {

}
