// A class for HeaderDHcp inherit directly from dhcp_header struct to wrap to python implementation
#ifndef _HEADER_DHCP_H
#define _HEADER_DHCP_H

#include <cstdint>
#include <cstring>
#include <string>
#include <DhcpLayer.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../utils.h"

namespace messagefactory
{
class HeaderDhcp : public pcpp::dhcp_header
{
public:
    HeaderDhcp() = default;

    HeaderDhcp(const dhcp_header& hdr) {
        *this = hdr;
    }
    // Accessing struct members is done directly as HeaderDhcp inherit dhcp_header from but getters and setters will be used later for python wrappers
    uint8_t getOpCode() const { return opCode; }
    void setOpCode(uint8_t value) { opCode = value; }

    
    uint8_t getHardwareType() const { return hardwareType; }
    void setHardwareType(uint8_t value) { hardwareType = value; }

    
    uint8_t getHardwareAddressLength() const { return hardwareAddressLength; }
    void setHardwareAddressLength(uint8_t value) { hardwareAddressLength = value; }

    
    uint8_t getHops() const { return hops; }
    void setHops(uint8_t value) { hops = value; }

    
    uint32_t getTransactionID() const { return ntohl(transactionID); }
    void setTransactionID(uint32_t value) { transactionID = htonl(value); }

    
    uint16_t getSecondsElapsed() const { return ntohs(secondsElapsed); }
    void setSecondsElapsed(uint16_t value) { secondsElapsed = htons(value); }

    
    uint16_t getFlags() const { return ntohs(flags); }
    void setFlags(uint16_t value) { flags = htons(value); }

    
    std::string getClientIpAddress() const 
    { 
        in_addr addr;
        addr.s_addr = clientIpAddress;
        return std::string(inet_ntoa(addr)); 
    }
    void setClientIpAddress(const std::string &value) 
    {   
        in_addr addr;
        inet_aton(value.c_str(), &addr);
        clientIpAddress = addr.s_addr;
    }

    std::string getYourIpAddress() const 
    { 
        in_addr addr;
        addr.s_addr = yourIpAddress;
        return std::string(inet_ntoa(addr)); 
    }

    void setYourIpAddress(const std::string &value)
    {   
        in_addr addr;
        inet_aton(value.c_str(), &addr);
        yourIpAddress = addr.s_addr;
    }

    std::string getServerIpAddress() const { 
        in_addr addr;
        addr.s_addr = serverIpAddress;
        return std::string(inet_ntoa(addr));
    }

    void setServerIpAddress(const std::string &value) 
    {   in_addr addr;
        inet_aton(value.c_str(), &addr);
        serverIpAddress = addr.s_addr;
    }

    
    std::string getRelayAgentIpAddress() const
    { 
        in_addr addr;
        addr.s_addr = gatewayIpAddress;
        return std::string(inet_ntoa(addr));
    }
    void setRelayAgentIpAddress(const std::string &value)
    {  
         in_addr addr;
        inet_aton(value.c_str(), &addr);
        gatewayIpAddress = addr.s_addr;
    }

    std::string getClientHardwareAddress() const 
    {
        std::ostringstream macStream;
        for (int i = 0; i < 6; ++i) {
            if (i > 0) {
                macStream << ":";
            }
            macStream << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(clientHardwareAddress[i]);
        }
        return macStream.str();
    }
    void setClientHardwareAddress(const std::string &address) 
    {
        std::istringstream stream(address);
        std::string byteString;
        int index = 0;

        while (std::getline(stream, byteString, ':') && index < 6) 
        {
            clientHardwareAddress[index++] = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
        }
    }

    std::string getServerName() const {
        return std::string(reinterpret_cast<const char*>(serverName), std::strlen(reinterpret_cast<const char*>(serverName)));
    }
    void setServerName(const std::string &name) {
        std::memset(serverName, 0, sizeof(serverName));
        std::memcpy(serverName, name.c_str(), std::min(name.size(), sizeof(serverName) - 1));
    }

    
    std::string getBootFilename() const {
        return std::string(reinterpret_cast<const char*>(bootFilename), std::strlen(reinterpret_cast<const char*>(bootFilename)));
    }
    void setBootFilename(const std::string &filename) {
        std::memset(bootFilename, 0, sizeof(bootFilename));
        std::memcpy(bootFilename, filename.c_str(), std::min(filename.size(), sizeof(bootFilename) - 1));
    }

    uint32_t getMagicNumber() const { return ntohl(magicNumber); }
    void setMagicNumber(uint32_t value) { magicNumber = htonl(value); }
};
}

#endif