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
        using BufferBlock = std::pair<char*, size_t>;

    public:
        SsBuffer() = default;
        SsBuffer(SsBuffer &) = delete;
        SsBuffer(SsBuffer &&) = delete;
        virtual ~SsBuffer();

        BufferBlock getBufferBlock(size_t except);
        void bufferBlockSizeFix(size_t except, size_t realSize);

    private:
        size_t _bufferStart = 0;
        size_t _bufferSize = 0;
        std::vector<char> _buffers;

    friend std::ostream &operator<<(std::ostream &out, SsBuffer &buffer);
};


#endif // __SHADOWSOCKS_BUFFER_INCLUDED__
