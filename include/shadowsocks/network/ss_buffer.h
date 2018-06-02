#ifndef __SHADOWSOCKS_BUFFER_INCLUDED__
#define __SHADOWSOCKS_BUFFER_INCLUDED__


#include "shadowsocks/ss_types.h"


/**
 * Class: SsBuffer
 *
 *
 */
class SsBuffer {
    public:
        using BufferBlock = std::pair<u_char*, size_t>;
        using DataBlock = std::vector<u_char>;
        using Data = u_char;

    public:
        SsBuffer() = default;
        SsBuffer(SsBuffer &) = delete;
        SsBuffer(SsBuffer &&) = delete;
        virtual ~SsBuffer();

        BufferBlock getBufferBlock(size_t except);
        void bufferBlockSizeFix(size_t except, size_t realSize);

        Data peekData(size_t index, Data invalid = 0xff);
        DataBlock getDataBlock(size_t except);
        DataBlock getDataBlock();

        bool checkDataSize(size_t except);

    private:
        size_t _bufferStart = 0;
        size_t _bufferSize = 0;
        std::vector<u_char> _buffers;

    friend std::ostream &operator<<(std::ostream &out, SsBuffer &buffer);
};


#endif // __SHADOWSOCKS_BUFFER_INCLUDED__
