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
    _buffers.resize(_bufferSize, 0x00);
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
        for (auto i = 0U; i < buffer._bufferSize; ++i) {
            std::printf("0x%02x ", buffer._buffers[buffer._bufferStart + i]);
        }
    } else {
        for (auto i = 0; i < BUFFER_PRINT_SIZE; ++i) {
            std::printf("0x%02x ", buffer._buffers[buffer._bufferStart + i]);
        }
        out << "\t...\t";
        for (auto i = -BUFFER_PRINT_SIZE; i < 0; ++i) {
            std::printf("0x%02x ", buffer._buffers[
                buffer._bufferStart + buffer._bufferSize + i]);
        }
    }

    return out;
}

// peek data only, not move
SsBuffer::Data SsBuffer::peekData(size_t index, Data invalid) {
    if (index > _bufferSize) {
        return invalid;
    }

    return static_cast<Data>(_buffers[_bufferStart + index]);
}

// get data from buffer when except size buffer exists
SsBuffer::DataBlock SsBuffer::getDataBlock(size_t except) {
    if (except > _bufferSize) {
        return SsBuffer::DataBlock();
    }

    DataBlock block;
    auto start = std::next(_buffers.begin(), _bufferStart);
    auto end = std::next(_buffers.begin(), _bufferStart + except);
    std::move(start, end, std::back_inserter(block));

    _bufferStart += except;
    _bufferSize -= except;
    if (2 * _bufferStart > _buffers.size()) {
        DataBlock buffers = getDataBlock();
        _buffers = std::move(buffers);
        _bufferStart = 0;
        _bufferSize = _buffers.size();
    }

    return block;
}

// get all buffer block
SsBuffer::DataBlock SsBuffer::getDataBlock() {
    DataBlock block;
    auto start = std::next(_buffers.begin(), _bufferStart);
    auto end = std::next(_buffers.begin(), _bufferStart + _bufferSize);
    std::move(start, end, std::back_inserter(block));

    _buffers.clear();
    _bufferStart = 0;
    _bufferSize = 0;
    return block;
}

// check buffer size
bool SsBuffer::checkDataSize(size_t except) {
    return _bufferSize >= except;
}

