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
        return std::vector<uint8_t>(
            m_packet.get()->getLayerOfType(pcpp::DHCP)->getData()
            , m_packet.get()->getLayerOfType(pcpp::DHCP)->getData() + m_packet.get()->getLayerOfType(pcpp::DHCP)->getDataLen()
            );
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
        return (pcpp::DhcpLayer::getOptionData(static_cast<pcpp::DhcpOptionTypes>(optionValue)).isNotNull());
    }
    std::vector<uint8_t> DhcpMessage::getOptionData(int optionValue)
    {
        if (this->hasOption(optionValue))
        {
            uint8_t* data = (pcpp::DhcpLayer::getOptionData(static_cast<pcpp::DhcpOptionTypes>(optionValue)).getValue());
            size_t dataSize = (pcpp::DhcpLayer::getOptionData(static_cast<pcpp::DhcpOptionTypes>(optionValue)).getDataSize());
            myVec.assign(data, data+dataSize);
        }
        else
        {
            PCPP_LOG_ERROR("Message Has no option " + std::to_string(optionValue));
        }
        return myVec;
    }
    void DhcpMessage::printPayloadAsByteStream()
    {
        std::ostringstream os;
        const uint8_t *_bytearray = m_packet.get()->getLayerOfType(pcpp::DHCP)->getData();
        const int _size = m_packet.get()->getLayerOfType(pcpp::DHCP)->getDataLen();
        
        std::cout << "[";
        for (int i = 0; i < _size; i++)
        {
            os << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(_bytearray[i]);
            if (i < _size - 1)
            {
                os << ",";
            }
        }
        os << "]";
        std::cout << os.str() << std::endl;
    }
}