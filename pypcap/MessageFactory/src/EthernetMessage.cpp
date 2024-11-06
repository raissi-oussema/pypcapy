#include "../include/EthernetMessage.h"

namespace messagefactory
{
    // Constructor to initialize Ethernet message with given source and destination MAC and EtherType
    EthernetMessage::EthernetMessage()
    {
        buildMessage();
    }

    void EthernetMessage::buildMessage()
    {
        m_packet.get()->addLayer(m_ethLayer.get());
    }
    pcpp::Layer* EthernetMessage::getLayer(pcpp::ProtocolType protocolType)
    {
        return m_packet.get()->getLayerOfType(protocolType);
    }
} // namespace messagefactory
