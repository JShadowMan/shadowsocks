#include "shadowsocks/network/ss_buffer.h"
#include "shadowsocks/ss_logger.h"


// SsBuffer destructor
SsBuffer::~SsBuffer() {
    SsLogger::debug("SsBuffer destruct with block size = %d", _buffers.size());
    _buffers.clear();
}

// create buffer block
SsBuffer::BufferBlock SsBuffer::getBufferBlock(size_t except) {
    _bufferSize += except;
    _buffers.resize(_bufferSize + except, 0x00);
    SsLogger::debug("Offset = %d, Size = %d, Capacity = %d",
                    _bufferStart, _bufferSize, _buffers.size());

    return std::make_pair(
        &_buffers[_bufferStart + _bufferSize - except], except
    );
}

// fix last buffer block size
void SsBuffer::bufferBlockSizeFix(size_t except, size_t realSize) {
    _bufferSize += -except + realSize;
    SsLogger::debug("FIXED Offset = %d, Size = %d, Capacity = %d",
                    _bufferStart, _bufferSize, _buffers.size());
}

// output buffer blocks
std::ostream &operator<<(std::ostream &out, SsBuffer &buffer) {
    out << "BufferSize: " << buffer._bufferSize << std::endl << "\t";
    if (buffer._bufferSize <= 2 * BUFFER_PRINT_SIZE) {
        for (auto i = buffer._bufferStart; i < buffer._bufferSize; ++i) {
            std::printf("0x%02x ", buffer._buffers[i]);
        }
    } else {
        for (auto i = buffer._bufferStart; i < BUFFER_PRINT_SIZE; ++i) {
            std::printf("0x%02x ", buffer._buffers[i]);
        }
        out << "\t...\t";
        for (auto i = -BUFFER_PRINT_SIZE; i < 0; ++i) {
            std::printf("0x%02x ", buffer._buffers[buffer._bufferSize + i]);
        }
    }

    return out;
}
