#ifndef __SHADOWSOCKS_NETWORK_INCLUDED__
#define __SHADOWSOCKS_NETWORK_INCLUDED__

#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_selector.h"
#include "shadowsocks/network/ss_buffer.h"


/**
 * Class: SsNetwork
 *
 *
 */
class SsNetwork : public SsSelectorCallbackInterface {
    public:
        enum class NetworkFamily : uint8_t {
            NF_INET_4 = AF_INET,
            NF_INET_6 = AF_INET6
        };

        enum class NetworkType : uint8_t {
            NT_RAW = SOCK_RAW,
            NT_TCP = SOCK_STREAM,
            NT_UDP = SOCK_DGRAM
        };

    protected:
        enum class NetworkState : uint8_t {
            NS_NONE = 0x00,
            NS_LISTEN = 0x01,
            NS_CONNECT = 0x02
        };

    public:
        SsNetwork(NetworkFamily family, NetworkType type);
        ~SsNetwork() override;

        bool listen(NetworkHost host, NetworkPort port);
        bool connect(NetworkHost host, NetworkPort port);

        inline SOCKET getSocket() const final {
            return _socket;
        }

        void selectorCallback(SsSelector::SelectorEvent event) final;

    protected:
        SsNetwork(SOCKET fd, sockaddr_storage &ss);

        virtual bool doListen(NetworkHost host, NetworkPort port) = 0;
        virtual bool doConnect(NetworkHost host, NetworkPort port) = 0;

        virtual void readableHandler() = 0;
        virtual void writableHandler() = 0;

        bool setSocketOpts() const;
        bool setNonBlocking() const;

        inline NetworkState getState() const {
            return _state;
        }

        SsBuffer::Buffer getBuffer();
        void bufferUpdate(SsBuffer::BufferBlockSize size);
        void printBuffer();
        bool bufferSizeCheck(unsigned int size);

        static sockaddr_storage socketAddr(NetworkHost host, NetworkPort port);

    private:
        void createSocket();

    private:
        SOCKET _socket;
        NetworkFamily _family;
        NetworkType _type;
        NetworkState _state;
        SsBuffer _buffers;

    friend std::ostream &operator<<(std::ostream &out, NetworkState state);
    friend std::ostream &operator<<(std::ostream &out, SsNetwork *network);
};


/**
 * Exception: SocketCreateError
 *
 *
 */
//SHADOWSOCKS_EXCEPTION(SocketCreateError);



/**
 * Exception: SocketStateError
 *
 *
 */
//SHADOWSOCKS_EXCEPTION(SocketStateError);


/**
 * Exception: SsNetworkClosed
 *
 *
 */
struct SsNetworkClosed : public std::exception {};


/* utility methods */
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkFamily family);
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkType type);


#endif // __SHADOWSOCKS_NETWORK_INCLUDED__
