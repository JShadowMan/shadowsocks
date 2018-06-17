#include "shadowsocks/ss_selector.h"
#include "shadowsocks/ss_logger.h"


// SsSelector constructor
SsSelector::SsSelector() : _objects({}) {
    SsLogger::debug("SsSelector created");
}

// add an object to selector
void SsSelector::add(SsSelector::Descriptor descriptor,
                     SsSelector::SelectorEvents events) {
    if (_objects.find(descriptor) == _objects.end()) {
        _objects[descriptor] = *events.begin();
        for (auto it = events.begin() + 1; it != events.end(); ++it) {
            _objects[descriptor] |= const_cast<>(*it);
        }
        SsLogger::debug("Descriptor = %d register %s", descriptor, events);
    }
}

// remove object from selector
void SsSelector::remove(SsSelector::Descriptor descriptor) {
    if (_objects.find(descriptor) == _objects.end()) {
        SsLogger::warning("Not found descriptor = %d in selector", descriptor);
    } else {
        _objects.erase(descriptor);
        SsLogger::debug("Remove descriptor = %d in selector", descriptor);
    }
}

// modify object events attribute
void SsSelector::movify(SsSelector::Descriptor descriptor,
                        SsSelector::SelectorEvents events) {
    if (_objects.find(descriptor) == _objects.end()) {
        SsLogger::warning("Not found descriptor = %d in selector", descriptor);
    } else {
        _objects[descriptor] = *events.begin();
        for (auto it = events.begin() + 1; it != events.end(); ++it) {
            _objects[descriptor] |= const_cast<>(*it);
        }
        SsLogger::debug("Descriptor = %d register %s", descriptor, events);
    }
}

// start select all objects
SsSelector::SelectResult SsSelector::select(int timeout) {
    return SsSelector::SelectResult();
}

// SsSelectorObject constructor
SsSelectorObject::SsSelectorObject(SsSelector::SelectorEvents events) {

}
