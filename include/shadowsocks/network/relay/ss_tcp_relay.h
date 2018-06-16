#ifndef __SHADOWSOCKS_TCP_RELAY_INCLUDED__
#define __SHADOWSOCKS_TCP_RELAY_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_tcp_network.h"


class SsTcpRelay {
    public:
        using Stream = std::vector<DATA_STREAM_UNIT>;
        using StreamCallback = std::function<void(Stream&, Stream&)>;

    public:
        void before(StreamCallback callback);
        void after(StreamCallback callback);

    private:
        std::shared_ptr<SsTcpNetwork> _source;
        std::map<
            SsNetwork::Descriptor, std::pair<SsTcpNetwork, SsTcpNetwork>
        > _streams;
};


#endif // __SHADOWSOCKS_TCP_RELAY_INCLUDED__
