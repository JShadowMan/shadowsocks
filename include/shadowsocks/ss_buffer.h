#ifndef __SHADOWSOCKS_BUFFER_INCLUDED__
#define __SHADOWSOCKS_BUFFER_INCLUDED__
#pragma once


// other shadowsocks headers
#include "ss_types.h"


/* `Ss_Package` class */
class Ss_Buffer {
    friend std::ostream &operator<<(std::ostream &out, const Ss_Buffer &p);

    public:
        using Buffer = std::pair<char*, int>;

    public:
        Ss_Buffer() = default;
        ~Ss_Buffer();

    public:
        Buffer &getBuffer();
        void updateBuffer(int count);
        void createBuffer();

    private:
        std::list<Buffer> _buffers;

        int _bytesTotal = 0;
        int _currentConsumeIndex = 0;
};


// friends functions
std::ostream &operator<<(std::ostream &out, const Ss_Buffer &p);


#endif // __SHADOWSOCKS_BUFFER_INCLUDED__
