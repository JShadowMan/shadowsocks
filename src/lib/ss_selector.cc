#include "shadowsocks/ss_selector.h"


// static members initializing
bool SsSelector::_eventLoopRunning = false;
std::map<SELECTOR_KEY, SELECTOR_VALUE> SsSelector::_events{};
std::map<
    SELECTOR_KEY, std::shared_ptr<SsSelectorCallbackInterface>
> SsSelector::_callbacks{};


// poll all socket descriptor
void SsSelector::startEventLoop() {
#ifdef __linux__
    SsLogger::verbose("event loop created by poll on linux");


#elif __windows__
    SsLogger::verbose("event loop created by select on windows");


#endif


    _eventLoopRunning = true;
    SsLogger::info("event loop started");
    while (_eventLoopRunning) {
        switch (triggerHandler(poll())) {
            case SelectorResult::SR_TIMEOUT: {
                SsLogger::debug("timeout for %d sec", SELECTOR_POLL_TIMEOUT);
                break;
            }
            case SelectorResult::SR_FAILURE: {
                SsLogger::error("select error occurs");
                break;
            }
            case SelectorResult::SR_SUCCESS: {
                SsLogger::debug("select succeed");
            }
        }
    }
}

// do poll all socket descriptor
#ifdef __linux__
SsSelector::PollCollection SsSelector::poll() {
    static pollfd fds[FD_SETSIZE] = {0};

    unsigned int index = 0;
    for (auto &pair : _events) {
        fds[index++] = pair.second;
    }

    PollCollection collection(SelectorResult::SR_SUCCESS, {});
    int total = ::poll(fds, _events.size(), SELECTOR_POLL_TIMEOUT * 1000);
    if (total == OPERATOR_FAILURE) {
        collection.first = SelectorResult::SR_FAILURE;
    } else if (total == 0) {
        collection.first = SelectorResult::SR_TIMEOUT;
    } else {
        for (index = 0; index < _events.size() && total > 0; ++index) {
            if (fds[index].revents != 0) {
                collection.second[fds[index].fd] = fds[index].revents;
                --total;
            }
        }
    }

    return collection;
}


#elif __windows__
SsSelector::PollCollection SsSelector::poll() {
    static FD_SET readable = {0};
    static FD_SET writable = {0};
    static timeval timeout{ .tv_sec = SELECTOR_POLL_TIMEOUT };

    FD_ZERO(&readable);
    FD_ZERO(&writable);

    for (auto &pair : _events) {
        // select cannot use to non-socket in windows
        auto fd = pair.first;
        if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO) {
            continue;
        }

        if (pair.second & SELECTOR_EVENT_IN) {
            FD_SET(fd, &readable);
        }

        if (pair.second & SELECTOR_EVENT_OUT) {
            FD_SET(fd, &writable);
        }
    }

    PollCollection collection(SelectorResult::SR_SUCCESS, {});
    int total = ::select(FD_SETSIZE, &readable, &writable, nullptr, &timeout);
    if (total == SOCKET_ERROR) {
        collection.first = SelectorResult::SR_FAILURE;
    } else if (total == 0) {
        collection.first = SelectorResult::SR_TIMEOUT;
    } else {
        auto hasEvent = false;
        collection.first = SelectorResult::SR_SUCCESS;
        for (auto &pair : _events) {
            if (FD_ISSET(pair.first, &readable)) {
                hasEvent = true;
                collection.second[pair.first] |= SELECTOR_EVENT_IN;
            }

            if (FD_ISSET(pair.first, &writable)) {
                hasEvent = true;
                collection.second[pair.first] |= SELECTOR_EVENT_OUT;
            }

            if (hasEvent && --total == 0) {
                break;
            }
        }
    }

    return collection;
}


#endif

// register a callback when socket available
void SsSelector::select(std::shared_ptr<SsSelectorCallbackInterface> cb,
                        SsSelector::SelectorEvents events) {
    auto fd = cb->getSocket();
    if (_events.find(fd) != _events.end()) {
        SsLogger::warning("duplicate register callback for socket = %d", fd);
    }

    _events[fd] = SELECTOR_VALUE_INIT(fd);
    _callbacks[fd] = cb;

    for (auto event : events) {
        SELECTOR_VALUE_ADD(_events[fd], static_cast<int>(event));
    }

    SsLogger::debug("callback registered for socket = %d", fd);
}

// stop event loop
void SsSelector::stopEventLoop() {
    _eventLoopRunning = false;
    SsLogger::debug("event loop has suspend");
}

// stop select for socket
void SsSelector::remove(SOCKET fd) {
    _events.erase(fd);
    _callbacks.erase(fd);
}

// trigger network callback
SsSelector::SelectorResult
SsSelector::triggerHandler(SsSelector::PollCollection collection) {
    if (collection.first != SelectorResult::SR_SUCCESS) {
        return collection.first;
    }

    for (auto &pair : collection.second) {
        auto &fd = pair.first;
        auto &events = pair.second;

        if (_callbacks.find(fd) == _callbacks.end()) {
            SsLogger::warning("cannot find callback for socket = %d", fd);
            continue;
        }

        if (events & SELECTOR_EVENT_IN) {
            _callbacks[fd]->selectorCallback(SelectorEvent::SE_READABLE);
        }
        if (events & SELECTOR_EVENT_OUT) {
            _callbacks[fd]->selectorCallback(SelectorEvent::SE_WRITABLE);
        }
    }

    return collection.first;
}
