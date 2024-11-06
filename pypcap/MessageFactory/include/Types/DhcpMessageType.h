#ifndef DHCP_MESSAGE_TYPES_H
#define DHCP_MESSAGE_TYPES_H
#include <stdint.h>

namespace messagefactory
{
    enum class DhcpMessageType : uint8_t
	{
		DHCP_UNKNOWN_MSG_TYPE = 0,
		DHCP_DISCOVER = 1,
		DHCP_OFFER = 2,
		DHCP_REQUEST = 3,
		DHCP_DECLINE = 4,
		DHCP_ACK = 5,
		DHCP_NAK = 6,
		DHCP_RELEASE = 7,
		DHCP_INFORM = 8
	};
	
}
#endif
