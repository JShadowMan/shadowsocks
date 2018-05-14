#include <iostream>
#include "shadowsocks/ss_package.h"


// Ss_Package destructor
Ss_Package::~Ss_Package() {
    std::cout << "package destructor" << std::endl;

    for (auto &buffer : _buffers) {
        delete[] buffer.first;

        buffer.first = nullptr;
        buffer.second = -1;
    }

    std::cout << "buffer cleaned" << std::endl;
}

// get last package
Ss_Package::Buffer &Ss_Package::getBuffer() {
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
void Ss_Package::updateBuffer(int count) {
    auto &last = getBuffer();

    _bytesTotal += count;
    if (count == BUFFER_SIZE - last.second) {
        createBuffer();
    } else {
        last.second += count;
    }
}

// update buffers
void Ss_Package::createBuffer() {
    if (!_buffers.empty()) {
        getBuffer().second = BUFFER_SIZE;
    }

    _buffers.emplace_back(new char[BUFFER_SIZE], 0);
}

// check package exists
bool Ss_Package::hasPackage() {
//    if (hasPackageHeader()) {
//        return true;
//    }
    return false;
}

// check package header exists
bool Ss_Package::hasPackageHeader() {
    return _bytesTotal >= PACKAGE_HEADER_SIZE;
}

// output package data
std::ostream &operator<<(std::ostream &out, const Ss_Package &p) {
    out << "BufferSize: " << p._buffers.size() << std::endl;
    for (auto i = 0U; i < p._buffers.size(); ++i) {
        auto it = std::next(p._buffers.begin(), i);
        out << "\tBuffer_" << i << "<" << BUFFER_GET_SIZE(*it) << ">: ";

        if (BUFFER_GET_SIZE(*it) <= 2 * BUFFER_PRINT_SIZE) {
            for (auto j = 0; j < BUFFER_GET_SIZE(*it); ++j) {
                out << *BUFFER_GET_SPEC_POINTER(*it, j);
            }
        } else if (BUFFER_GET_SIZE(*it) > 2 * BUFFER_PRINT_SIZE) {
            auto index = 0;
            for (auto j = BUFFER_PRINT_SIZE; abs(j) <= BUFFER_PRINT_SIZE; --j) {
                if (j > 0) {
                    out << *BUFFER_GET_SPEC_POINTER(*it, BUFFER_PRINT_SIZE - j);
                } else if (j == 0) {
                    out << " ... ";
                } else {
                    index = BUFFER_GET_SIZE(*it) - 1 - BUFFER_PRINT_SIZE - j;
                    if (index >= 0) {
                        out << *BUFFER_GET_SPEC_POINTER(*it, index);
                    }
                }
            }
        }

        out << std::endl;
    }

    return out;
}
