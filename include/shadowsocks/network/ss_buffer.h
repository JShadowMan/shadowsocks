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
        using BufferPosition = char *;
        using BufferStart = BufferPosition;
        using AvailableBuffer = BufferPosition;
        using BufferBlockSize = int;
        using AvailableBufferSize = int;
        using BufferBlock = std::pair<
            std::pair<BufferStart, AvailableBuffer>,
            std::pair<BufferBlockSize, AvailableBufferSize>
        >;
        using Buffer = std::pair<BufferPosition, AvailableBufferSize>;
        using Data = std::pair<BufferPosition, AvailableBufferSize>;

    public:
        SsBuffer() = default;
        SsBuffer(SsBuffer &) = delete;
        SsBuffer(SsBuffer &&) = delete;
        virtual ~SsBuffer();

        Buffer getBuffer();
        void update(BufferBlockSize size);
        bool checkSize(unsigned int size);

        Data getData();
        void consumeData(int size);

    private:
        void createBufferBlock();

    private:
        BufferPosition _dataStart;
        unsigned _totalBytes = 0;
        std::list<SsBuffer::BufferBlock> _buffers;

    friend std::ostream &operator<<(std::ostream &out, SsBuffer &buffer);
};


#endif // __SHADOWSOCKS_BUFFER_INCLUDED__
