#include <shlobj.h>
#include "shadowsocks/ss_selector.h"
#include "shadowsocks/ss_logger.h"


// SsSelector constructor
SsSelector::SsSelector() : _objects({}) {
    DBG("SsSelector created");
}

// SsSelector destructor
SsSelector::~SsSelector() {
    DBG("SsSelector closed");
}

// add an object to selector
void SsSelector::add(SsSelector::Descriptor descriptor,
                     SsSelector::SelectorEvents events) {
    if (_objects.find(descriptor) != _objects.end()) {
        WARN("Duplicate register descriptor = %d to selector", descriptor);
    } else {
        DBG("Register descriptor = %d to selector with events = %s",
              descriptor, events);
        for (auto &event : events) {
            _objects[descriptor] |= static_cast<>(event);
        }
    }
}

// remove object from selector
void SsSelector::remove(SsSelector::Descriptor descriptor) {
    if (_objects.find(descriptor) == _objects.end()) {
        WARN("Not found descriptor = %d in selector", descriptor);
    } else {
        DBG("Remove descriptor = %d in selector", descriptor);
        _objects.erase(descriptor);
    }
}

// modify object events attribute
void SsSelector::movify(SsSelector::Descriptor descriptor,
                        SsSelector::SelectorEvents events) {
    if (_objects.find(descriptor) == _objects.end()) {
        WARN("Not found descriptor = %d in selector", descriptor);
    } else {
        DBG("Modify descriptor = %d events to %s", descriptor, events);
        _objects[descriptor] = 0;
        for (auto &event : events) {
            _objects[descriptor] |= static_cast<>(event);
        }
    }
}

// start select all objects
#if defined(__platform_linux__)
SsSelector::SelectResult SsSelector::select(int timeout) {
    static std::vector<pollfd> fds;
}
#elif defined(__platform_windows__)
SsSelector::SelectResult SsSelector::select(int timeout) {
    static FD_SET readable;
    static FD_SET writable;
    static timeval tv = { .tv_sec = timeout };

    FD_ZERO(&readable);
    FD_ZERO(&writable);

    for (auto &pair : _objects) {
        if (pair.second & SELECTOR_EVENT_IN) {
            FD_SET(pair.first, &readable);
        }
        if (pair.second & SELECTOR_EVENT_OUT) {
            FD_SET(pair.first, &writable);
        }
    }

    SelectResult result;
    int selectResult = ::select(FD_SETSIZE, &readable, &writable, nullptr, &tv);
    if (selectResult == OPERATOR_FAILURE) {
        result.first = SelectorState::SS_FAILURE;
    } else if (selectResult == 0) {
        result.first = SelectorState::SS_TIMEOUT;
    } else {
        result.first = SelectorState::SS_SUCCESS;

        uint8_t descriptorEvent = 0;
        auto descriptorReadable = false;
        auto descriptorWritable = false;
        for (auto &pair : _objects) {
            if (FD_ISSET(pair.first, &readable)) {
                descriptorReadable = true;
                descriptorEvent |= SELECTOR_EVENT_IN;
            }
            if (FD_ISSET(pair.first, &writable)) {
                descriptorWritable = true;
                descriptorEvent |= SELECTOR_EVENT_OUT;
            }

            if (descriptorReadable || descriptorWritable) {
                result.second.push_back({pair.first, {
                    descriptorReadable, descriptorWritable
                }});

                if (--selectResult == 0) {
                    break;
                }
            }
        }
    }

    return result;
}
#endif