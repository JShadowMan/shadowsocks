#ifndef __SHADOWSOCKS_PACKAGE_INCLUDED__
#define __SHADOWSOCKS_PACKAGE_INCLUDED__
#pragma once


// other shadowsocks headers
#include "ss_types.h"


/* `Ss_Package` class */
class Ss_Package {
    friend std::ostream &operator<<(std::ostream &out, const Ss_Package &p);

    public:
        using Package = std::pair<char*, int>;
        static constexpr int PACKAGE_SIZE = BUFFER_SIZE;

    public:
        Ss_Package() = default;

    public:
        Package &get();
        void update(int count);
        void update();

    private:
        std::list<Package> _buffers;
};


// friends functions
std::ostream &operator<<(std::ostream &out, const Ss_Package &p);


#endif // __SHADOWSOCKS_PACKAGE_INCLUDED__
