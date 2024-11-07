#ifndef _DHCP_MESSAGE_H_
#define _DHCP_MESSAGE_H_

#include <DhcpLayer.h>
#include <IPv4Layer.h>
#include <UdpLayer.h>
#include <Packet.h>
#include "IMessageBasic.h"
#include "Headers/HeaderIPv4.h"
#include "Headers/HeaderUdp.h"
#include "Headers/HeaderDhcp.h"

namespace messagefactory
{
    class DhcpMessage : public IMessageBasic, public pcpp::DhcpLayer
{
public:
    DhcpMessage();
    void buildMessage() override;
    HeaderDhcp* getDhcpHeader();
    HeaderUdp* getUdpHeader();
    std::vector<uint8_t> getBytes();
    void addOption(int option, std::vector<uint8_t> optionData);
    bool hasOption(int optionType);
    std::vector<uint8_t> getOptionData(int optionValue);
    void printPayloadAsByteStream();

    ~DhcpMessage() noexcept {};
    
private:
    void setUdpLayer();
    std::vector<uint8_t> myVec;
    std::unique_ptr<pcpp::UdpLayer> m_udpLayer;
};

} 
#endif