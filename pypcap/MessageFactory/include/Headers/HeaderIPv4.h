#ifndef HEADER_IPV4_H
#define HEADER_IPV4_H

#include <stdint.h>
#include <string>
#include <IPv4Layer.h>
#include <IpAddress.h>
#include <arpa/inet.h>

namespace messagefactory
{
    #pragma pack(push, 1)
    class HeaderIPv4 : public pcpp::iphdr
    {
    public:
        HeaderIPv4() = default;
        HeaderIPv4 (const iphdr& hdr){
        *this = hdr;
        }

        uint8_t getInternetHeaderLength() const { return internetHeaderLength; }
        void setInternetHeaderLength(uint8_t length) { internetHeaderLength = length; }

        uint8_t getIpVersion() const { return ipVersion; }
        void setIpVersion(uint8_t version) { ipVersion = version; }

        uint8_t getTypeOfService() const { return typeOfService; }
        void setTypeOfService(uint8_t service) { typeOfService = service; }

        uint16_t getTotalLength() const { return ntohs(totalLength); }
        void setTotalLength(uint16_t length) { totalLength = htons(length); }

        uint16_t getIpId() const { return ntohs(ipId); }
        void setIpId(uint16_t id) { ipId = htons(id); }

        uint16_t getFragmentOffset() const { return ntohs(fragmentOffset); }
        void setFragmentOffset(uint16_t offset) { fragmentOffset = htons(offset); }

        uint8_t getTimeToLive() const { return timeToLive; }
        void setTimeToLive(uint8_t ttl) { timeToLive = ttl; }

        uint8_t getProtocol() const { return protocol; }
        void setProtocol(uint8_t protocolValue) { protocol = protocolValue; }

        uint16_t getHeaderChecksum() const { return ntohs(headerChecksum); }
        void setHeaderChecksum(uint16_t checksum) { headerChecksum = htons(checksum); }

        std::string getSrcIPAddress() const { return pcpp::IPv4Address(ipSrc).toString(); }
        void setSrcIPAddress(const std::string& ipAddress) { ipSrc = (pcpp::IPv4Address(ipAddress)).toInt(); }

        std::string getDstIPAddress() const { return pcpp::IPv4Address(ipDst).toString(); }
        void setDstIPAddress(const std::string& ipAddress) { ipDst = (pcpp::IPv4Address(ipAddress)).toInt(); }
    };
    #pragma pack(pop)
}
#endif
