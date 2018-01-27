#ifndef __SHADOWSOCKS_CRYPTO_INCLUDED__
#define __SHADOWSOCKS_CRYPTO_INCLUDED__

#include <utility>
#include <string>

#define SPLIT_KEY(__key_iv) (__key_iv).first
#define SPLIT_IV(__key_iv) (__key_iv).second


class Ss_Crypto {
    public:
        using Ss_KeyIv = std::pair<unsigned char *, unsigned char *>;

    public:
        static Ss_KeyIv evp_bytes_to_key(std::string password);

    public:
        static void init_crypto();

    private:
        static bool crypto_init_flag;
};


#endif // __SHADOWSOCKS_CRYPTO_INCLUDED__
