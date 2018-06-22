#include "shadowsocks/ss_selector.h"
#include "shadowsocks/ss_logger.h"


// SsSelector constructor
SsSelector::SsSelector() : _objects({}) {
    DBG("SsSelector created");
}

// SsSelector destructor
SsSelector::~SsSelector() {
    _objects.clear();
    DBG("SsSelector closed");
}

// add an object to selector
void SsSelector::add(SsSelector::Descriptor descriptor,
                     SsSelector::SelectorEvents events) {
    if (descriptorExists(descriptor)) {
        WARN("Duplicate register descriptor = %d to selector", descriptor);
    } else {
        DBG("Register descriptor = %d to selector with events = %s",
              descriptor, "EVENTS");

#if defined(__platform_linux__)
        pollfd fd = { .fd = descriptor, .events = 0 };
        for (auto &event : events) {
            fd.events |= static_cast<uint8_t>(event);
        }
        _objects.push_back(fd);
#elif defined(__platform_windows__)
        for (auto &event : events) {
            _objects[descriptor] |= static_cast<uint8_t>(event);
        }
#endif
    }
}

// remove object from selector
void SsSelector::remove(SsSelector::Descriptor descriptor) {
    if (descriptorExists(descriptor)) {
        WARN("Not found descriptor = %d in selector", descriptor);
    } else {
        DBG("Remove descriptor = %d in selector", descriptor);
#if defined(__platform_linux__)
        _objects.erase(std::remove_if(_objects.begin(), _objects.end(),
            [&] (pollfd &fd) {
                return fd.fd == descriptor;
            }
        ), _objects.end());
#elif defined(__platform_windows__)
        _objects.erase(descriptor);
#endif
    }
}

// modify object events attribute
void SsSelector::movify(SsSelector::Descriptor descriptor,
                        SsSelector::SelectorEvents events) {
    if (descriptorExists(descriptor)) {
        WARN("Not found descriptor = %d in selector", descriptor);
    } else {
        DBG("Modify descriptor = %d events to %s", descriptor, "EVENTS");
#if defined(__platform_linux__)
        auto it = std::find_if(_objects.begin(), _objects.end(),
            [&] (pollfd &fd){
                return fd.fd == descriptor;
            }
        );

        it->events = 0;
        for (auto &event : events) {
            it->events |= static_cast<uint8_t>(event);
        }
#elif defined(__platform_windows__)
        _objects[descriptor] = 0;
        for (auto &event : events) {
            _objects[descriptor] |= static_cast<uint8_t>(event);
        }
#endif
    }
}

// start select all objects
#if defined(__platform_linux__)
SsSelector::SelectResult SsSelector::select(int timeout) {
    SelectResult result;
    int pollResult = ::poll(&_objects[0], _objects.size(), timeout * 1000);
    if (pollResult == OPERATOR_FAILURE) {
        result.first = SelectorState::SS_FAILURE;
    } else if (pollResult == 0) {
        result.first = SelectorState::SS_TIMEOUT;
    } else {
        result.first = SelectorState::SS_SUCCESS;

        for (auto &fd : _objects) {
            auto descriptorReadable = false;
            auto descriptorWritable = false;

            if (fd.revents != 0) {
                if (fd.revents & SELECTOR_EVENT_IN) {
                    descriptorReadable = true;
                }

                if (fd.revents & SELECTOR_EVENT_OUT) {
                    descriptorWritable = true;
                }

                result.second.push_back({fd.fd, {
                    descriptorReadable, descriptorWritable
                }});

                if (--pollResult == 0) {
                    break;
                }
            }
        }
    }

    return result;
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

        for (auto &pair : _objects) {
            auto descriptorReadable = false;
            auto descriptorWritable = false;

            if (FD_ISSET(pair.first, &readable)) {
                descriptorReadable = true;
            }
            if (FD_ISSET(pair.first, &writable)) {
                descriptorWritable = true;
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

// check descriptor exists
bool SsSelector::descriptorExists(SsSelector::Descriptor &descriptor) {
#if defined(__platform_linux__)
    return std::find_if(_objects.begin(), _objects.end(), [&] (pollfd &fd) {
        return fd.fd == descriptor;
    }) != _objects.end();
#elif defined(__platform_windows__)
    return _objects.find(descriptor) == _objects.end();
#endif
}
