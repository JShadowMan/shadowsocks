#include "shadowsocks/ss_selector.h"


// static members initializing
bool SsSelector::_eventLoopRunning = false;
std::map<SELECTOR_KEY, SELECTOR_VALUE> SsSelector::_sockets{};
std::map<SELECTOR_KEY, SsSelectorCallbackInterface*> SsSelector::_callbacks{};


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
        switch (doPoll()) {
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
SsSelector::SelectorResult SsSelector::doPoll() {
    static pollfd fds[64] = {0};

    int index = 0;
    for (auto &s : _sockets) {
        fds[index++] = s.second;
    }

    int total = ::poll(fds, _sockets.size(), SELECTOR_POLL_TIMEOUT * 1000);
    if (total == OPERATOR_FAILURE) {
        return SelectorResult::SR_FAILURE;
    }

    if (total == 0) {
        return SelectorResult::SR_TIMEOUT;
    } else {
        int size = _sockets.size();
        for (index = 0; index < size && total > 0; index++) {
            auto fd = fds[index].fd;
            if (_callbacks.find(fd) == _callbacks.end()) {
                SsLogger::warning("cannot find callback for socket = %d", fd);
                continue;
            }

            if (fds[index].revents != 0) {
                if (fds[index].revents & SELECTOR_EVENT_IN) {
                    _callbacks[fd]->selectorCallback(SelectorEvent::SE_READABLE);
                }

                if (fds[index].revents & SELECTOR_EVENT_OUT) {
                    _callbacks[fd]->selectorCallback(SelectorEvent::SE_WRITABLE);
                }

                --total;
            }
        }
    }

    return SelectorResult::SR_SUCCESS;
}


#elif __windows__
SsSelector::SelectorResult SsSelector::doPoll() {
    static FD_SET readable = {0};
    static FD_SET writable = {0};
    static timeval timeout{ .tv_sec = SELECTOR_POLL_TIMEOUT };

    FD_ZERO(&readable);
    FD_ZERO(&writable);

    for (auto &pair : _sockets) {
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

    int total = ::select(FD_SETSIZE, &readable, &writable, nullptr, &timeout);
    if (total == SOCKET_ERROR) {
        return SelectorResult::SR_FAILURE;
    }
    if (total == 0) {
        return SelectorResult::SR_TIMEOUT;
    }

    for (auto &pair : _sockets) {
        if (total <= 0) {
            break;
        }

        auto fd = pair.first;
        if (_callbacks.find(fd) == _callbacks.end()) {
            SsLogger::warning("cannot find callback for socket = %d", fd);
            continue;
        }

        if (FD_ISSET(fd, &readable)) {
            --total;
            _callbacks[fd]->selectorCallback(SelectorEvent::SE_READABLE);
        }

        if (FD_ISSET(fd, &writable)) {
            --total;
            _callbacks[fd]->selectorCallback(SelectorEvent::SE_WRITABLE);
        }
    }

    return SelectorResult::SR_SUCCESS;
}


#endif

// register a callback when socket available
void SsSelector::select(SsSelectorCallbackInterface &cb,
                        SsSelector::SelectorEvents events) {
    auto fd = cb.getSocket();
    if (_sockets.find(fd) != _sockets.end()) {
        SsLogger::warning("duplicate register callback for socket = %d", fd);
    }

    _sockets[fd] = SELECTOR_VALUE_INIT(fd);
    _callbacks[fd] = &cb;

    for (auto event : events) {
        SELECTOR_VALUE_ADD(_sockets[fd], static_cast<int>(event));
    }

    SsLogger::debug("callback registered for socket = %d", fd);
}

// stop event loop
void SsSelector::stopEventLoop() {
    _eventLoopRunning = false;
    SsLogger::debug("event loop has suspend");
}
