#include "shadowsocks/client/ss_client.h"
#include "shadowsocks/ss_selector.h"


// static members initializing
std::map<std::string, std::shared_ptr<SsClient>> SsClient::_clients{};


// SsClient constructor
SsClient::SsClient(NetworkHost host, NetworkPort port) :
    _host(host), _port(port) {
}

// start client to receive browser data and send encrypt data to ss-server
void SsClient::startProxyService() {
    for (auto &pair : _clients) {
        auto &client = pair.second;

        client->_tcpRelay.startProxy(client->_host, client->_port);
        client->_udpRelay.startProxy(client->_host, client->_port);
    }

    SsSelector::startEventLoop();
}

// create shadowsocks client
void SsClient::createClient(NetworkHost host, NetworkPort port) {
    std::string key = host;
    key += ":" + port;

    if (_clients.find(key) != _clients.end()) {
        SsLogger::error("duplicate shadowsocks client on %s:%d", host, port);
        return;
    }

    _clients[key] = std::make_shared<SsClient>(host, port);
}

// shutdown service and cleanup environments
void SsClient::shutdownProxyService() {
    _clients.clear();
}
