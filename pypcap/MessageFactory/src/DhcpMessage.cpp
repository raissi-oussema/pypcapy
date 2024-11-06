#include "../include/DhcpMessage.h"

namespace messagefactory{
    DhcpMessage::DhcpMessage()
    : m_udpLayer(std::make_unique<pcpp::UdpLayer>(68, 67))
    {
        buildMessage();
    }

    void DhcpMessage::buildMessage()
    {
        setEthLayer();
        setIpLayer();
        setUdpLayer();
        DhcpLayer::setMessageType(pcpp::DhcpMessageType::DHCP_DISCOVER);
        DhcpLayer::addOption(pcpp::DhcpOptionBuilder(pcpp::DHCPOPT_END, nullptr, 0));
        DhcpLayer::computeCalculateFields();

        m_packet.get()->addLayer(this, false);
        m_packet.get()->computeCalculateFields();
    }
    HeaderUdp* DhcpMessage::getUdpHeader()
    {
        return reinterpret_cast<HeaderUdp*>(m_udpLayer.get()->getUdpHeader());
    }
    void DhcpMessage::setUdpLayer()
    {
        m_packet.get()->addLayer(m_udpLayer.get(), false);
    }
    HeaderDhcp* DhcpMessage::getDhcpHeader()
    {
        return reinterpret_cast<HeaderDhcp*>(DhcpLayer::getDhcpHeader());
    }
    std::vector<uint8_t> DhcpMessage::getBytes()
    {
        return std::vector<uint8_t>(DhcpLayer::getData(), DhcpLayer::getData()+DhcpLayer::getDataLen());
    }
    void DhcpMessage::addOption(int option, std::vector<uint8_t> data)
    {
        if (option >= -1 && option <= 255) 
        {
            pcpp::DhcpOptionTypes _option   = static_cast<pcpp::DhcpOptionTypes>(option);
            uint8_t* _optionValue           = data.data();
            uint8_t _optionLength           = data.size();

            const pcpp::DhcpOptionBuilder &optionBuilder = pcpp::DhcpOptionBuilder(_option, _optionValue, _optionLength);
            pcpp::DhcpLayer::addOption(optionBuilder);
        }
        else 
        {
            PCPP_LOG_ERROR("Could not set invalid option value, try value between 0..255");
        }
    }
    bool DhcpMessage::hasOption(int optionValue)
    {
        return (getOptionData(static_cast<pcpp::DhcpOptionTypes>(optionValue)).isNotNull());
    }
}