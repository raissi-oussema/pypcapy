#ifndef _ETHERNET_MESSAGE_H_
#define _ETHERNET_MESSAGE_H_

#include <Layer.h>
#include <EthLayer.h>
#include <VlanLayer.h>
#include <MacAddress.h>
#include <Packet.h>
#include <unordered_map>
#include <PcapLiveDevice.h>
#include <memory>
#include <PcapLiveDeviceList.h>
#include <iostream>
#include <optional>
#include <memory> // For std::unique_ptr
#include <Logger.h>
#include "IMessageBasic.h"

namespace messagefactory
{
    class EthernetMessage : public IMessageBasic
    {
    public:
        EthernetMessage();
        void buildMessage() override;
        
        virtual ~EthernetMessage() noexcept override {}; // Use default destructor
        pcpp::Layer* getLayer(pcpp::ProtocolType protocolType);
    };
}
#endif