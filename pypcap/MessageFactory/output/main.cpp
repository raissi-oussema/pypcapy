#include "../include/DhcpMessage.h"
#include "../include/EthernetMessage.h"
#include "../include/utils.h"

using namespace std;

int main()
{
    const std::string &src_mac = "f4:8c:50:e0:3e:a9";
    const std::string &dst_mac = "ff:ff:ff:ff:ff:ff";
    const std::string bytes = "fffffffffffff48c50e03ea908004500013c00004000401139b200000000ffffffff0044004301283fdf010106003375ebec0001000000000000000000000000000000000000f48c50e03ea900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000638253633501013d0701f48c50e03ea937110102060c0f1a1c79032128292a77f9fc11390202403204c0a801110c046b616c69ff";

    messagefactory::EthernetMessage eth_msg;
    eth_msg.send("wlan0");
    eth_msg.setAllBytes(messagefactory::bytesFromHex(bytes));
    eth_msg.send("wlan0");

    messagefactory::DhcpMessage dhcp_msg;
    dhcp_msg.getEthernetHeader()->setSourceMacAddr(src_mac);
    dhcp_msg.getEthernetHeader()->setDestinationMacAddr(dst_mac);
    dhcp_msg.getEthernetHeader()->setEtherType(messagefactory::EtherTypes::PYPCAP_ETHERTYPE_IPX);

    dhcp_msg.getIPv4Header()->setSrcIPAddress("0.0.0.0");
    dhcp_msg.getIPv4Header()->setDstIPAddress("255.255.255.255");
    dhcp_msg.getIPv4Header()->setTimeToLive(64);
    
    dhcp_msg.getUdpHeader()->setSourcePort(66);
    dhcp_msg.getUdpHeader()->setDestinationPort(67);
    //dhcp_msg.getUdpHeader()->setLength(234);
    dhcp_msg.send("wlan0");

    dhcp_msg.getDhcpHeader()->setHardwareType(0x01);
    std::cout << "HardwareType: " << unsigned(dhcp_msg.getDhcpHeader()->getHardwareType()) << std::endl;
    
    dhcp_msg.getDhcpHeader()->setHardwareAddressLength(0x06);
    std::cout << "HardwareAddressLength: " << unsigned(dhcp_msg.getDhcpHeader()->getHardwareAddressLength()) << std::endl;
    
    dhcp_msg.getDhcpHeader()->setHops(0x0);
    std::cout << "Hops: " << unsigned(dhcp_msg.getDhcpHeader()->getHops()) << std::endl;
    
    dhcp_msg.getDhcpHeader()->setTransactionID(0x3375ebec);
    std::cout << "TransactionID: " << dhcp_msg.getDhcpHeader()->getTransactionID() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setSecondsElapsed(1);
    std::cout << "SecondsElapsed: " << dhcp_msg.getDhcpHeader()->getSecondsElapsed() << std::endl;

    dhcp_msg.getDhcpHeader()->setFlags(0x0000);
    std::cout << "Bootp Flags: " << dhcp_msg.getDhcpHeader()->getFlags() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setClientIpAddress("192.168.1.6");
    std::cout << "ClientIP address: " << dhcp_msg.getDhcpHeader()->getClientIpAddress() << std::endl;

    dhcp_msg.getDhcpHeader()->setYourIpAddress("192.168.1.70");
    std::cout << "YourIP address: " << dhcp_msg.getDhcpHeader()->getYourIpAddress() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setRelayAgentIpAddress("10.10.0.1");
    std::cout << "RelayAgent address: " << dhcp_msg.getDhcpHeader()->getRelayAgentIpAddress() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setServerName("OussemaServer");
    std::cout << "ServerName: " << dhcp_msg.getDhcpHeader()->getServerName() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setServerIpAddress("192.168.1.1");
    std::cout << "ServerIpAddress: " << dhcp_msg.getDhcpHeader()->getServerIpAddress() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setClientHardwareAddress("f4:8c:50:e0:3e:a9");
    std::cout << "ClientHardwareAddress: " << dhcp_msg.getDhcpHeader()->getClientHardwareAddress() << std::endl;
    
    dhcp_msg.getDhcpHeader()->setMagicNumber(0x63825363);
    std::cout << "MagicNumber: " << dhcp_msg.getDhcpHeader()->getMagicNumber() << std::endl;
    
    dhcp_msg.setMessageType(pcpp::DhcpMessageType::DHCP_DISCOVER);
    

    // Add Requested IP Address option
    std::vector<uint8_t> opDataRequestedIp {0x01, 0xf4, 0x8c, 0x50, 0xe0, 0x3e, 0xa9};
    std::vector<uint8_t> opData {0x02, 0x40};
    dhcp_msg.addOption(57, opData);
    dhcp_msg.addOption(61, opDataRequestedIp);
    std::cout << dhcp_msg.hasOption(61) << std::endl;
    std::cout << dhcp_msg.hasOption(57) << std::endl;
    std::cout << dhcp_msg.hasOption(255) << std::endl;
    std::cout << dhcp_msg.hasOption(100) << std::endl;
    std::vector<uint8_t> record = dhcp_msg.getOptionData(30) ;
    dhcp_msg.printRawPacketAsByteStream();
    for (int i = 0; i < record.size(); i++)
    {
        std::cout << unsigned(record[i]) << std::endl;
    }
    // Add Parameter Request List option (Example: requesting subnet mask and router)



    for (int i = 0; i <= 3; i++)
    {
        dhcp_msg.send("wlan0");
    }
}
    /*const std::string src_mac = "11:22:33:44:55:66";
    const std::string dst_mac = "aa:bb:cc:dd:ee:ff";
    messagefactory::EthernetMessage eth_msg;
    messagefactory::DhcpMessage dhcp_msg;
    dhcp_msg.getAllBytes();
    cout << dhcp_msg.toString();
    std::cout << eth_msg.getDestinationMacAddr() << std::endl;
    std::cout << eth_msg.getSourceMacAddr() << std::endl;

    eth_msg.setSourceMacAddr(src_mac);
    eth_msg.setDestMacAddr(dst_mac);

    std::cout << "Hello" << std::endl;
    const uint8_t* bytearray = eth_msg.getRawData();
    const int size = eth_msg.getRawDataLength();
    eth_msg.printRawPacketByteStream();

    std::cout << eth_msg.getDestinationMacAddr() << std::endl;
    std::cout << eth_msg.getSourceMacAddr() << std::endl;

    const std::string arrStr = "b4b0245dc900f48c50e03ea9080045000034bce6400040060fbdc0a8011198c713a09dc801bb47a7ca46e5d3ffdf8010011c80df00000101080a1466bb7b9b7e841b";
    const std::vector<uint8_t> arr = bytesFromHex(arrStr);

    eth_msg.setAllBytes(arr);

    //std::vector<uint8_t> b = eth_msg.getAllBytes();
    //for (uint8_t e: b)
    //{
    //    cout<<static_cast<int>(e)<<endl;
    //}
    eth_msg.printRawPacketByteStream();
    
    std::cout << eth_msg.getDestinationMacAddr() << std::endl;
    std::cout << eth_msg.getSourceMacAddr() << std::endl;

    const std::string _arrStr = "f48c50e03ea9b4b0245dc9000800450000370000400038112b394a7d0b47c0a8011101bb853700236c4a4768869821d18a4d9dbd76491dab67138460fdb58d733662bd1bdf";
    std::vector<uint8_t> _arr = bytesFromHex(_arrStr);
    const uint8_t *_bytes = _arr.data();
    const size_t _length = _arr.size();

    eth_msg.setAllBytes(_bytes, _length);

    std::cout << eth_msg.getDestinationMacAddr() << std::endl;
    std::cout << eth_msg.getSourceMacAddr() << std::endl;

    eth_msg.setAllBytes(arr);

    std::cout << eth_msg.getDestinationMacAddr() << std::endl;
    std::cout << eth_msg.getSourceMacAddr() << std::endl;

    eth_msg.setAllBytes(arr);

    std::cout << eth_msg.getDestinationMacAddr() << std::endl;
    std::cout << eth_msg.getSourceMacAddr() << std::endl;
    for (int i = 0; i <= 150; i++)
    {  
        eth_msg.send("wlan0");
    }*/