#include "shadowsocks/client/ss_client.h"
#include "shadowsocks/ss_selector.h"


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
