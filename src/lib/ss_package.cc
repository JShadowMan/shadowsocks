#include <iostream>
#include "shadowsocks/ss_package.h"


// get last package
Ss_Package::Package &Ss_Package::get() {
    if (_buffers.empty()) {
        update();
    }

    auto &lastPackage = _buffers.back();
    if (lastPackage.second == PACKAGE_SIZE) {
        update();
        return _buffers.back();
    }
    return lastPackage;
}

// update buffers when last package not full
void Ss_Package::update(int count) {
    auto &last = get();

    if (count == BUFFER_SIZE - last.second) {
        update();
    } else {
        last.second += count;
    }
}

// update buffers
void Ss_Package::update() {
    if (!_buffers.empty()) {
        auto &last = get();
        last.second = BUFFER_SIZE;
    }

    _buffers.emplace_back(new char[BUFFER_SIZE], 0);
}
