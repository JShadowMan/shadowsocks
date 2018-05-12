#ifndef __SHADOWSOCKS_PACKAGE_INCLUDED__
#define __SHADOWSOCKS_PACKAGE_INCLUDED__
#pragma once


// other shadowsocks headers
#include "ss_types.h"


/* `Ss_Package` class */
class Ss_Package {
    friend std::ostream &operator<<(std::ostream &out, const Ss_Package &p);

    public:
        using Buffer = std::pair<char*, int>;

    public:
        Ss_Package() = default;

    public:
        Buffer &getBuffer();
        void update(int count);
        void update();

    private:
        std::list<Buffer> _buffers;
};


// friends functions
std::ostream &operator<<(std::ostream &out, const Ss_Package &p);


#endif // __SHADOWSOCKS_PACKAGE_INCLUDED__
