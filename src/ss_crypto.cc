#include <iostream>
#include <openssl/evp.h>
#include "shadowsocks/ss_crypto.h"

/* Initializing Ss_Crypto static members */
bool Ss_Crypto::crypto_init_flag = false;


/* Definition Ss_Crypto methods */
Ss_Crypto::Ss_KeyIv Ss_Crypto::evp_bytes_to_key(std::string password) {
    init_crypto();

    const EVP_CIPHER *cipher = nullptr;
    const EVP_MD *digest = nullptr;

    unsigned char key[EVP_MAX_KEY_LENGTH] = {0};
    unsigned char iv[EVP_MAX_IV_LENGTH] = {0};

    if (!(cipher = EVP_get_cipherbyname("aes-256-cfb"))) {
        std::cerr << "No such cipher" << std::endl;
        exit(1);
    }

    if (!(digest = EVP_get_digestbyname("md5"))) {
        std::cerr << "No such digest" << std::endl;
        exit(1);
    }

    if (!EVP_BytesToKey(cipher, digest, nullptr,
                        (unsigned char *) password.c_str(), password.size(),
                        1,
                        key, iv)) {
        std::cerr << "EVP_BytesToKey failed" << std::endl;
        exit(1);
    }

    return std::make_pair(key, iv);
}


void Ss_Crypto::init_crypto() {
    if (!crypto_init_flag) {
        OpenSSL_add_all_ciphers();
        OpenSSL_add_all_digests();

        crypto_init_flag = true;
    }
}
