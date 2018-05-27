#include "shadowsocks/client/ss_client.h"
#include "shadowsocks/ss_selector.h"


// static members initializing
std::map<std::string, std::shared_ptr<SsClient>> SsClient::_clients{};


// SsClient constructor
SsClient::SsClient(NetworkHost host, NetworkPort port) :
    _host(host), _port(port) {
}

// start client to receive browser data and send encrypt data to ss-server
void SsClient::startEventLoop() {
    _tcpRelay.startProxy(_host, _port);
    _udpRelay.startProxy(_host, _port);

    SsSelector::startEventLoop();
}

// check daemon exists
bool SsClient::hasDaemon() {
    return false;
}

// create shadowsocks client
void SsClient::createClient(NetworkHost host, NetworkPort port) {
    std::string key = host;
    key += ":" + port;

    if (_clients.find(key) != _clients.end()) {
        SsLogger::error("duplicate shadowsocks client on %s:%d", host, port);
    }
}
