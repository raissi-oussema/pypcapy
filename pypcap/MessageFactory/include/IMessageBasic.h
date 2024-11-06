#ifndef IMESSAGEBASIC_H
#define IMESSAGEBASIC_H


#include "Headers/HeaderIPv4.h"
#include "Headers/HeaderEthernet.h"
#include <EthLayer.h>
#include <IPv4Layer.h>
#include <IPv6Layer.h>
#include <PcapLiveDevice.h>
#include <unordered_map>
#include <PcapLiveDeviceList.h>
#include <Logger.h>
#include <string>

namespace messagefactory
{

    class IMessageBasic
    {
    public:
        virtual ~IMessageBasic();
        virtual std::string packetToString();
        virtual void buildMessage() = 0;

        IMessageBasic();

        void setEthLayer();
        pcpp::EthLayer* getEthLayer();
        
        void setIpLayer();
        pcpp::IPv4Layer* getIpLayer();
        
        HeaderEthernet* getEthernetHeader() const;
        HeaderIPv4* getIPv4Header() const;
        
        void setAllBytes(const uint8_t *bytes, size_t length);
        void setAllBytes(std::vector<uint8_t> bytesVector);


        std::vector<uint8_t> getAllBytes();
        void printRawPacketAsByteStream();
        void send(std::string interfaceName);
        void setComputeBeforeSend(bool op);
        bool getComputeBeforeSend();
       
    protected:
        void clearOpenedDevicesPool();
        void insertIntoOpendDevicesPool(const std::string &interface, pcpp::PcapLiveDevice *dev);
        std::unique_ptr<pcpp::Packet> m_packet;
        std::unique_ptr<pcpp::RawPacket> m_rawPacket;
        std::unique_ptr<pcpp::EthLayer> m_ethLayer;
        std::unique_ptr<pcpp::IPv4Layer> m_ipv4Layer;
        std::unordered_map<std::string, pcpp::PcapLiveDevice *> openedDevicesPool;
        std::vector<uint8_t> rawDataVector;
        bool computeBeforeSend;
    };

} // namespace MessageBuilder

#endif // IMESSAGEBASIC_H
