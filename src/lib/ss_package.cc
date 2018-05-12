#include <iostream>
#include "shadowsocks/ss_package.h"


// get last package
Ss_Package::Buffer &Ss_Package::getBuffer() {
    if (_buffers.empty()) {
        update();
    }

    auto &lastPackage = _buffers.back();
    if (lastPackage.second == BUFFER_SIZE) {
        update();
        return _buffers.back();
    }
    return lastPackage;
}

// update buffers when last package not full
void Ss_Package::update(int count) {
    auto &last = getBuffer();

    if (count == BUFFER_SIZE - last.second) {
        update();
    } else {
        last.second += count;
    }
}

// update buffers
void Ss_Package::update() {
    if (!_buffers.empty()) {
        getBuffer().second = BUFFER_SIZE;
    }

    _buffers.emplace_back(new char[BUFFER_SIZE], 0);
}

// output package data
std::ostream &operator<<(std::ostream &out, const Ss_Package &p) {
    out << "BufferSize: " << p._buffers.size() << std::endl;
    for (auto i = 0U; i < p._buffers.size(); ++i) {
        out << "\tBuffer_" << i << ": ";

        auto it = std::next(p._buffers.begin(), i);
        for (auto j = BUFFER_PRINT_SIZE; abs(j) <= BUFFER_PRINT_SIZE; --j) {
            if (j > 0) {
                out << *BUFFER_GET_SPEC_POINTER(*it, BUFFER_PRINT_SIZE - j);
            } else if (j == 0) {
                out << " ... ";
            } else {
                out << *BUFFER_GET_SPEC_POINTER(
                        *it, BUFFER_GET_SIZE(*it) - 1 - BUFFER_PRINT_SIZE - j);
            }
        }

        out << std::endl;
    }

    return out;
}
