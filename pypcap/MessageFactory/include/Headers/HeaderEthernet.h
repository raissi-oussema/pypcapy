#ifndef HEADER_ETHERNET_H
#define HEADER_ETHERNET_H
#include "../Types/EtherTypes.h"
#include <VlanLayer.h>
#include <EthLayer.h>
#include <arpa/inet.h>

namespace messagefactory
{
    class HeaderEthernet : pcpp::ether_header
    {
    public:
        HeaderEthernet() = default;
        HeaderEthernet(const ether_header &hdr)
        {
            *this = hdr;
        }
        void setSourceMacAddr(const std::string &_srcMac) {pcpp::MacAddress(_srcMac).copyTo(srcMac);}
        const std::string getSourceMacAddr() const {return pcpp::MacAddress(srcMac).toString();}

        void setDestinationMacAddr(const std::string &_dstMac) {pcpp::MacAddress(_dstMac).copyTo(dstMac);}
        const std::string getDestinationMacAddr() const {return pcpp::MacAddress(dstMac).toString();}
        
        void setEtherType(EtherTypes _etherType) {etherType = htons(static_cast<uint16_t> (_etherType));}
        const EtherTypes getEtherType() const {return static_cast<EtherTypes> (ntohs(etherType));}
    };
}

#endif