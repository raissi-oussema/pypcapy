#ifndef _HEADER_UDP_
#define _HEADER_UDP_


#include <UdpLayer.h>
#include <arpa/inet.h>

namespace messagefactory
{
    #pragma pack(push, 1)
    class HeaderUdp : public pcpp::udphdr
    {
    public:
        HeaderUdp() = default;
        HeaderUdp (const udphdr& hdr){
        *this = hdr;
        }

        uint16_t getSourcePort() const { return ntohs(portSrc); }
        void setSourcePort(uint16_t _portSrc) { portSrc = htons(_portSrc); }

        uint16_t getDestinationPort() const { return ntohs(portDst); }
        void setDestinationPort(uint16_t _portDst) { portDst = htons(_portDst); }

        uint16_t getLength() const { return ntohs(length); }
        void setLength(uint16_t _length) { length = htons(_length); }

        uint16_t getHeaderChecksum() const { return ntohs(headerChecksum); }
        void setHeaderChecksum(uint16_t _headerChecksum) { headerChecksum = htons(_headerChecksum); }
    };
}
#endif