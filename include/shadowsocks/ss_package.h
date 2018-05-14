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
        ~Ss_Package();

    public:
        Buffer &getBuffer();
        void updateBuffer(int count);
        void createBuffer();

    public:
        bool hasPackage();

    private:
        bool hasPackageHeader();

    private:
        std::list<Buffer> _buffers;
        std::list<Buffer> _outputs;

        int _bytesTotal = 0;
        int _currentConsumeIndex = 0;
};


// friends functions
std::ostream &operator<<(std::ostream &out, const Ss_Package &p);


#endif // __SHADOWSOCKS_PACKAGE_INCLUDED__
