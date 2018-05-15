#include <iostream>
#include <shadowsocks/ss_core.h>
#include "shadowsocks/ss_buffer.h"


// Ss_Package destructor
Ss_Buffer::~Ss_Buffer() {
    std::cout << "package destructor" << std::endl;

    for (auto &buffer : _buffers) {
        delete[] buffer.first;

        buffer.first = nullptr;
        buffer.second = -1;
    }

    std::cout << "buffer cleaned" << std::endl;
}

// get last package
Ss_Buffer::Buffer &Ss_Buffer::getBuffer() {
    if (_buffers.empty()) {
        createBuffer();
    }

    auto &lastPackage = _buffers.back();
    if (lastPackage.second == BUFFER_SIZE) {
        createBuffer();
        return _buffers.back();
    }
    return lastPackage;
}

// update buffers when last package not full
void Ss_Buffer::updateBuffer(int count) {
    auto &last = getBuffer();

    _bytesTotal += count;
    if (count == BUFFER_SIZE - last.second) {
        createBuffer();
    } else {
        last.second += count;
    }
}

// update buffers
void Ss_Buffer::createBuffer() {
    if (!_buffers.empty()) {
        getBuffer().second = BUFFER_SIZE;
    }

    _buffers.emplace_back(new char[BUFFER_SIZE], 0);
}

// output package data
std::ostream &operator<<(std::ostream &out, const Ss_Buffer &p) {
    out << "BufferSize: " << p._buffers.size() << std::endl;
    for (auto i = 0U; i < p._buffers.size(); ++i) {
        auto it = std::next(p._buffers.begin(), i);
        std::printf("\tBuffer_%d<%4d>: ", i, BUFFER_GET_SIZE(*it));

        if (BUFFER_GET_SIZE(*it) <= 2 * BUFFER_PRINT_SIZE) {
            for (auto j = 0; j < BUFFER_GET_SIZE(*it); ++j) {
                PRINT_BYTE(*BUFFER_SPEC_POINTER(*it, j));
            }
        } else if (BUFFER_GET_SIZE(*it) > 2 * BUFFER_PRINT_SIZE) {
            auto index = 0;
            for (auto j = BUFFER_PRINT_SIZE; abs(j) <= BUFFER_PRINT_SIZE; --j) {
                if (j > 0) {
                    PRINT_BYTE(*BUFFER_SPEC_POINTER(*it, BUFFER_PRINT_SIZE - j));
                } else if (j == 0) {
                    out << "\t...\t";
                } else {
                    index = BUFFER_GET_SIZE(*it) - 1 - BUFFER_PRINT_SIZE - j;
                    if (index >= 0) {
                        PRINT_BYTE(*BUFFER_SPEC_POINTER(*it, index));
                    }
                }
            }
        }

        out << std::endl;
    }

    return out;
}
