#ifndef __SHADOWSOCKS_NETWORK_INCLUDED__
#define __SHADOWSOCKS_NETWORK_INCLUDED__


/* socket headers */
#include <sys/types.h>
#include <sys/socket.h>


/* `Ss_Network` class */
class Ss_Network {
    public:
        using NetworkFamily = int;

    public:
        static constexpr NetworkFamily INET4 = AF_INET;
        static constexpr NetworkFamily INET6 = AF_INET6;

    public:
        Ss_Network();
        explicit Ss_Network(NetworkFamily family);
        ~Ss_Network();

    public:
        bool listen(const char *host, int port);

    private:
        bool createSocket(const char *host);

    private:
        using NetworkSocket = int;

    private:
        NetworkFamily _family;
        NetworkSocket _socket;
};



#endif // __SHADOWSOCKS_NETWORK_INCLUDED__
