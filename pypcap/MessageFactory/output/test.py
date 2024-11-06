from pypcap import *
# Create MAC addresses
src_mac = "11:22:33:44:55:66"
dst_mac = "aa:bb:cc:dd:ee:ff"
opDataRequestedIp = [0x01, 0xf4, 0x8c, 0x50, 0xe0, 0x3e, 0xa9]
# Create Ethernet message
eth_msg = EthernetMessage()
dhcp_msg = DhcpMessage()
print(dhcp_msg.ethernet_header.mac_address_source)
print(dhcp_msg.ethernet_header.mac_address_destination)
print(dhcp_msg.ethernet_header.ether_type)

dhcp_msg.ethernet_header.mac_address_source = src_mac
dhcp_msg.ethernet_header.mac_address_destination = dst_mac
dhcp_msg.ethernet_header.ether_type = EtherTypes.PYPCAP_ETHERTYPE_ETHBRIDGE
print(dhcp_msg.ethernet_header.mac_address_source)
print(dhcp_msg.ethernet_header.mac_address_destination)
print(dhcp_msg.ethernet_header.ether_type)

print(dhcp_msg.udp_header.port_source)
print(dhcp_msg.udp_header.port_destination)
print(dhcp_msg.udp_header.length)
print(dhcp_msg.udp_header.header_checksum)

print(dhcp_msg.ipv4_header.ip_id)
print(dhcp_msg.ipv4_header.fragment_offset)
print(dhcp_msg.ipv4_header.header_checksum)
print(dhcp_msg.ipv4_header.ip_version)
print(dhcp_msg.ipv4_header.destination_ip_address)
print(dhcp_msg.ipv4_header.time_to_live)

dhcp_msg.ipv4_header.destination_ip_address = "20.20.20.20"
dhcp_msg.ipv4_header.source_ip_address = "192.20.50.20"
dhcp_msg.ipv4_header.ip_id = 0x12
dhcp_msg.dhcp_header.transaction_id = 0x23242526
dhcp_msg.ipv4_header.time_to_live = 64
dhcp_msg.message_type  = DhcpMessageType.DHCP_INFORM
dhcp_msg.add_option(61, opDataRequestedIp)
print(dhcp_msg.has_option(61))
print(dhcp_msg.has_option(55))
print(dhcp_msg.message_type)

print(dhcp_msg.ipv4_header.source_ip_address)
print(dhcp_msg.ipv4_header.destination_ip_address)
print("before send: ", list(dhcp_msg.get_bytes()))
dhcp_msg.send("wlan0")
print("after send: ", list(dhcp_msg.get_bytes()))
"""print(eth_msg.ethernet_header.mac_address_source)
print(eth_msg.ethernet_header.mac_address_destination)
print(eth_msg.ethernet_header.ether_type)

eth_msg.ethernet_header.mac_address_source = src_mac
eth_msg.ethernet_header.mac_address_destination = dst_mac
eth_msg.ethernet_header.ether_type = EtherTypes.PYPCAP_ETHERTYPE_AARP

print(eth_msg.ethernet_header.mac_address_source)
print(eth_msg.ethernet_header.mac_address_destination)
print(eth_msg.ethernet_header.ether_type)

eth_msg.send("wlan0")

arr0 = bytearray([i for i in range(30)])
arr = bytes.fromhex("22")
# print(type(arr0))
eth_msg.set_all_bytes(arr)

print(list(eth_msg.get_all_bytes()))
eth_msg.send("wlan0")
eth_msg.set_all_bytes(arr0)
print(list(eth_msg.get_all_bytes()))
eth_msg.send("wlan0")
helloClient = bytes.fromhex("a6d4b5e0315cf48c50e03ea908004500005bf493400040060ab8c0a83297ac409bd1967201bb0bae58e33c92638d801801e9178c00000101080a68108a2310702e0117030300227150d6d85d8677058f99015480759993779c666f55fa76ebb4bbe078b6b4947dee13")
eth_msg.set_all_bytes(helloClient)
print(list(eth_msg.get_all_bytes()))
eth_msg.send("wlan0")"""

