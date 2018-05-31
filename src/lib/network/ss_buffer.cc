#include "shadowsocks/network/ss_buffer.h"
#include "shadowsocks/ss_logger.h"


// SsBuffer destructor
SsBuffer::~SsBuffer() {
    SsLogger::debug("SsBuffer destruct with block size = %d", _buffers.size());

    for (auto &pair : _buffers) {
        delete[] pair.first.first;
        pair.first.first = nullptr;
        pair.first.second = nullptr;

        pair.second.first = 0;
        pair.second.second = 0;
    }
}

// get buffer position
SsBuffer::Buffer SsBuffer::getBuffer() {
    if (_buffers.empty()) {
        createBufferBlock();
    }

    auto &available = _buffers.back();
    return std::make_pair(available.first.second, available.second.second);
}

// update buffer
void SsBuffer::update(SsBuffer::BufferBlockSize size) {
    auto &available = _buffers.back();
    available.second.second -= size;
    available.first.second += size;
    _totalBytes += size;

    if (available.second.second == 0) {
        createBufferBlock();
    }
}

// create new buffer block
void SsBuffer::createBufferBlock() {
    if (!_buffers.empty()) {
        _buffers.back().second.second = 0;
        _buffers.back().first.second = nullptr;
    }

    auto bufferBlock = new char[BUFFER_BLOCK_SIZE];
    _buffers.emplace_back(
        std::make_pair(bufferBlock, bufferBlock),
        std::make_pair(BUFFER_BLOCK_SIZE, BUFFER_BLOCK_SIZE)
    );
    SsLogger::debug("buffer block created, with size = %d", _buffers.size());
}

// output buffer
std::ostream &operator<<(std::ostream &out, SsBuffer &buffer) {
    out << "BufferBlockSize: " << buffer._buffers.size() << std::endl;
    for (auto i = 0U; i < buffer._buffers.size(); ++i) {
        auto it = std::next(buffer._buffers.begin(), i);
        std::printf("\tBuffer_%d<%4d>: ", i, BLOCK_GET_SIZE(*it));

        if (BLOCK_GET_SIZE(*it) <= 2 * BUFFER_PRINT_SIZE) {
            for (auto j = 0; j < BLOCK_GET_SIZE(*it); ++j) {
                PRINT_BYTE(*BLOCK_SPEC_POS(*it, j));
            }
        } else if (BLOCK_GET_SIZE(*it) > 2 * BUFFER_PRINT_SIZE) {
            auto index = 0;
            for (auto j = BUFFER_PRINT_SIZE; abs(j) <= BUFFER_PRINT_SIZE; --j) {
                if (j > 0) {
                    PRINT_BYTE(*BLOCK_SPEC_POS(*it, BUFFER_PRINT_SIZE - j));
                } else if (j == 0) {
                    out << "\t...\t";
                } else {
                    index = BLOCK_GET_SIZE(*it) - 1 - BUFFER_PRINT_SIZE - j;
                    if (index >= 0) {
                        PRINT_BYTE(*BLOCK_SPEC_POS(*it, index));
                    }
                }
            }
        }

        out << std::endl;
    }

    return out;
}

// check buffer size
bool SsBuffer::checkSize(unsigned int size) {
    return size <= _totalBytes;
}

// consume data
SsBuffer::Data SsBuffer::getData() {
    auto &front = _buffers.front();

    return std::make_pair(_dataStart, front.first.second - _dataStart);
}

// update data position
void SsBuffer::consumeData(int size) {
}
