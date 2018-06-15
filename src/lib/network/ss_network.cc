#include "shadowsocks/network/ss_network.h"
#include "shadowsocks/ss_logger.h"


// SsNetwork constructor
SsNetwork::SsNetwork(SsNetwork::NetworkFamily family,
                     SsNetwork::NetworkType type) :
    _family(family), _type(type), _descriptor(0) {
    SsLogger::debug("%s created", this);
}

// SsNetwork constructor
SsNetwork::SsNetwork(SsNetwork::Descriptor descriptor,
                     SsNetwork::Address address, SsNetwork::NetworkType type):
    _family(NetworkFamily::NF_INET_4), _type(type),
    _descriptor(descriptor) {
}

// SsNetwork destructor
SsNetwork::~SsNetwork() {
    SsLogger::debug("%s closed", this);
}

// get network descriptor
SsNetwork::Descriptor SsNetwork::getDescriptor() {
    return _descriptor;
}

// connecting to host:port
void SsNetwork::connect(SsNetwork::HostName host, SsNetwork::HostPort port) {
    if (_state != NetworkState::NS_NONE) {
        SsLogger::warning("cannot convert state form %s to %s",
                          _state, NetworkState::NS_ESTABLISHED);
    }
    _state = NetworkState::NS_ESTABLISHED;

    doConnect(host, port);
}

// listening on host:port
void SsNetwork::listen(SsNetwork::HostName host, SsNetwork::HostPort port) {
    if (_state != NetworkState::NS_NONE) {
        SsLogger::warning("cannot convert state form %s to %s",
                          _state, NetworkState::NS_LISTEN);
    }
    _state = NetworkState::NS_LISTEN;

    doListen(host, port);
}

// connecting to host:port
void SsNetwork::doConnect(SsNetwork::HostName host, SsNetwork::HostPort port) {
    SsLogger::info("%s connecting to %s:%d", this, host, port);
}

// listening on host:port
void SsNetwork::doListen(SsNetwork::HostName host, SsNetwork::HostPort port) {
    SsLogger::info("%s listening on %s:%d", this, host, port);
}

// from server accept a new client
SsNetwork::ConnectingTuple SsNetwork::accept() {
    Descriptor client;
    auto address = std::make_shared<SsNetwork::Address>();
#if defined(__platform_linux__)
    socklen_t length = sizeof(SsNetwork::Address);
#elif defined(__platform_windows__)
    int length = sizeof(SsNetwork::Address);
#endif

    if (_state != NetworkState::NS_LISTEN) {
        SsLogger::error("accept client from non-listening network");
        return {INVALID_SOCKET, address};
    }

    client = ::accept(getDescriptor(), (sockaddr*) address.get(), &length);
    if (client == INVALID_SOCKET || client < 0) {
        SsLogger::error("accept connection error from %s", this);
    }

    return {client, address};
}

// network toString and output
std::ostream &operator<<(std::ostream &o, SsNetwork *network) {
    o << "SsNetwork["
      << "descriptor=" << network->_descriptor << ","
      << "family=" << network->_family << ","
      << "type=" << network->_type << ","
      << "state=" << network->_state
      << "]";

    return o;
}

// network family output
std::ostream &operator<<(std::ostream &o, SsNetwork::NetworkFamily &family) {
    switch (family) {
        case SsNetwork::NetworkFamily::NF_INET_4: o << "INET4"; break;
        case SsNetwork::NetworkFamily::NF_INET_6: o << "INET6"; break;
    }

    return o;
}

// network type output
std::ostream &operator<<(std::ostream &o, SsNetwork::NetworkType &type) {
    switch (type) {
        case SsNetwork::NetworkType::NT_TCP: o << "TCP"; break;
        case SsNetwork::NetworkType::NT_UDP: o << "UDP"; break;
        case SsNetwork::NetworkType::NT_RAW: o << "RAW"; break;
    }

    return o;
}

// network state output
std::ostream &operator<<(std::ostream &o, SsNetwork::NetworkState &state) {
    switch (state) {
        case SsNetwork::NetworkState::NS_NONE: o << "NONE"; break;
        case SsNetwork::NetworkState::NS_LISTEN: o << "LISTEN"; break;
        case SsNetwork::NetworkState::NS_ESTABLISHED: o << "ESTABLISHED"; break;
    }

    return o;
}

