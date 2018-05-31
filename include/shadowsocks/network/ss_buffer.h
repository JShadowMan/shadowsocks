#ifndef __SHADOWSOCKS_BUFFER_INCLUDED__
#define __SHADOWSOCKS_BUFFER_INCLUDED__


#include "shadowsocks/ss_types.h"


class SsBuffer {
    public:
        using BufferPosition = char *;
        using BufferStart = BufferPosition;
        using BufferEnd = BufferPosition;
        using BufferBlockSize = int;
        using AvailableBufferSize = int;
        using BufferBlock = std::pair<
            std::pair<BufferStart, BufferEnd>,
            std::pair<BufferBlockSize, AvailableBufferSize>
        >;
        using Buffer = std::pair<BufferPosition, AvailableBufferSize>;

    public:
        SsBuffer() = default;
        SsBuffer(SsBuffer &) = delete;
        SsBuffer(SsBuffer &&) = delete;
        ~SsBuffer();

        Buffer getBuffer();
        void update(BufferBlockSize size);

    private:
        void createBufferBlock();

    private:
        std::list<SsBuffer::BufferBlock> _buffers;

    friend std::ostream &operator<<(std::ostream &out, SsBuffer &buffer);
};


#endif // __SHADOWSOCKS_BUFFER_INCLUDED__
