#include "../include/IMessageBasic.h"

namespace messagefactory
{
    IMessageBasic::IMessageBasic() 
    : 
    m_packet(std::make_unique<pcpp::Packet>())
    , m_ethLayer(std::make_unique<pcpp::EthLayer>(pcpp::MacAddress("00:00:00:00:00:00"), pcpp::MacAddress("ff:ff:ff:ff:ff:ff"), 0x800))
    , m_rawPacket(std::make_unique<pcpp::RawPacket>())
    , m_ipv4Layer(std::make_unique<pcpp::IPv4Layer>())
    , computeBeforeSend(true)
    {}

    void IMessageBasic::setEthLayer() { m_packet.get()->addLayer(m_ethLayer.get(), false); }
    pcpp::EthLayer *IMessageBasic::getEthLayer() { return m_ethLayer.get(); }

    void IMessageBasic::setAllBytes(const uint8_t *bytes, size_t length)
    {
        rawDataVector.assign(bytes, bytes + length);
        size_t _length = rawDataVector.size();

        if (length < sizeof(pcpp::ether_header))
        {
            PCPP_LOG_ERROR("Byte array is too small for an Ethernet Packet.");
            // throw std::invalid_argument("Byte array is too small for an Ethernet Packet.");
        }

        if (length >= sizeof(pcpp::ether_header))
        {
            timeval timestamp;
            timespec timespec;
            gettimeofday(&timestamp, nullptr);
            TIMEVAL_TO_TIMESPEC(&timestamp, &timespec);

            m_rawPacket.get()->initWithRawData(rawDataVector.data(), _length, timespec);
            m_packet.get()->setRawPacket(m_rawPacket.get(), false);

            m_packet.get()->computeCalculateFields();
            PCPP_LOG(pcpp::Logger::Info, m_packet.get()->toString());
            PCPP_LOG(pcpp::Logger::Info, "Inserted to current Message !");
            // std::cout << m_packet.get()->toString() << "Inserted to current EthernetMessage !" << std::endl;
        }
    }
    void IMessageBasic::setAllBytes(std::vector<uint8_t> bytesVector)
    {
        rawDataVector.assign(bytesVector.data(), bytesVector.data() + bytesVector.size());
        size_t length = rawDataVector.size();

        if (length < sizeof(pcpp::ether_header))
        {
            PCPP_LOG_ERROR("Byte array is too small for an Ethernet Packet.");
            return;
            // throw std::invalid_argument("Byte array is too small for an Ethernet Packet.");
        }

        if (length >= sizeof(pcpp::ether_header))
        {
            timeval timestamp;
            timespec timespec;
            gettimeofday(&timestamp, nullptr);
            TIMEVAL_TO_TIMESPEC(&timestamp, &timespec);

            m_rawPacket.get()->initWithRawData(rawDataVector.data(), length, timespec);
            m_packet.get()->setRawPacket(m_rawPacket.get(), false);

            m_packet.get()->computeCalculateFields();
            PCPP_LOG(pcpp::Logger::Info, m_packet.get()->toString());
            PCPP_LOG(pcpp::Logger::Info, "Inserted to current EthernetMessage !");
            // std::cout << m_packet.get()->toString() << "Inserted to current EthernetMessage !" << std::endl;
        }
    }

    void IMessageBasic::setIpLayer() { m_packet.get()->addLayer(m_ipv4Layer.get(), false); }
    pcpp::IPv4Layer *IMessageBasic::getIpLayer() { return m_ipv4Layer.get(); }

    HeaderIPv4 *IMessageBasic::getIPv4Header() const { return reinterpret_cast<HeaderIPv4 *>(m_ipv4Layer.get()->getIPv4Header()); }
    HeaderEthernet *IMessageBasic::getEthernetHeader() const { return reinterpret_cast<HeaderEthernet *>(m_ethLayer.get()->getEthHeader()); }

    std::vector<uint8_t> IMessageBasic::getAllBytes() { return std::vector<uint8_t>(m_packet.get()->getRawPacket()->getRawData(), m_packet.get()->getRawPacket()->getRawData() + m_packet.get()->getRawPacket()->getRawDataLen()); }

    void IMessageBasic::insertIntoOpendDevicesPool(const std::string &interface, pcpp::PcapLiveDevice *dev) { openedDevicesPool.emplace(interface, dev); }
    
    std::string IMessageBasic::packetToString() { return m_packet.get()->toString(); }

    void IMessageBasic::setComputeBeforeSend(bool op){ computeBeforeSend = op; }
    
    bool IMessageBasic::getComputeBeforeSend(){ return computeBeforeSend; }

    void IMessageBasic::send(std::string interfaceName)
    {
        auto it = openedDevicesPool.find(interfaceName);
        if (it == openedDevicesPool.end())
        {
            // Find and open the device
            auto dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(interfaceName.c_str());
            if (!dev || !dev->open())
            {
                PCPP_LOG_ERROR("Could not open device: " + interfaceName);
                // throw std::runtime_error("Could not open device: " + interfaceName);
            }
            insertIntoOpendDevicesPool(interfaceName, dev);
        }

        auto dev = openedDevicesPool.at(interfaceName);
        
        if (computeBeforeSend) {m_packet.get()->computeCalculateFields();}

        if (!dev->sendPacket(m_packet.get()))
        {
            PCPP_LOG_ERROR("Could not send packet on device: " + interfaceName);
            // throw std::runtime_error("Could not send packet on device: " + interfaceName);
        }
        else
            PCPP_LOG(pcpp::Logger::Info, "Packet sent on " + interfaceName);
    }
    void IMessageBasic::clearOpenedDevicesPool()
    {
        for (auto &[interface, dev] : openedDevicesPool)
        {
            dev->close();
        }
        openedDevicesPool.clear();
    }
    IMessageBasic::~IMessageBasic() {}
    void IMessageBasic::printRawPacketAsByteStream()
    {
        std::ostringstream os;
        const uint8_t *_bytearray = m_packet.get()->getRawPacket()->getRawData();
        const int _size = m_packet.get()->getRawPacket()->getRawDataLen();
        
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
