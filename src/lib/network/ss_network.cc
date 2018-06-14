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
