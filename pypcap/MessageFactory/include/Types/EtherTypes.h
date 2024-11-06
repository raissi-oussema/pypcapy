// EtherTypes.h
#ifndef ETHERTYPES_H
#define ETHERTYPES_H
#include <stdint.h>

namespace messagefactory
{
    enum class EtherTypes : uint16_t
    {
        PYPCAP_ETHERTYPE_IP = 0x0800,
        PYPCAP_ETHERTYPE_ARP = 0x0806,
        PYPCAP_ETHERTYPE_ETHBRIDGE = 0x6558,
        PYPCAP_ETHERTYPE_REVARP = 0x8035,
        PYPCAP_ETHERTYPE_AT = 0x809B,
        PYPCAP_ETHERTYPE_AARP = 0x80F3,
        PYPCAP_ETHERTYPE_VLAN = 0x8100,
        PYPCAP_ETHERTYPE_IPX = 0x8137,
        PYPCAP_ETHERTYPE_IPV6 = 0x86DD,
        PYPCAP_ETHERTYPE_LOOPBACK = 0x9000,
        PYPCAP_ETHERTYPE_PPPOED = 0x8863,
        PYPCAP_ETHERTYPE_PPPOES = 0x8864,
        PYPCAP_ETHERTYPE_MPLS = 0x8847,
        PYPCAP_ETHERTYPE_PPP = 0x880B,
        PYPCAP_ETHERTYPE_ROCEV1 = 0x8915,
        PYPCAP_ETHERTYPE_IEEE_802_1AD = 0x88A8,
        PYPCAP_ETHERTYPE_WAKE_ON_LAN = 0x0842
    };
}
#endif // ETHERTYPES_H