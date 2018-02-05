#ifndef __SHADOWSOCKS_CRYPTO_INCLUDED__
#define __SHADOWSOCKS_CRYPTO_INCLUDED__

#include <utility>


/* Class Ss_Crypto */
class Ss_Crypto {
    public:
        using CryptoKey = std::pair<char *, char *>;

    public:
        static CryptoKey bytes_to_key(char *password);
};


#endif  // __SHADOWSOCKS_CRYPTO_INCLUDED__