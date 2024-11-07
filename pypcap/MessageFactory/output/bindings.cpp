#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include "../include/Headers/HeaderEthernet.h"
#include "../include/Headers/HeaderIPv4.h"
#include "../include/EthernetMessage.h"
#include "../include/DhcpMessage.h"
#include "../include/Types/EtherTypes.h"
#include "../include/Types/DhcpMessageType.h"
#include <string>
#include <pybind11/numpy.h> 
#include <pybind11/buffer_info.h> 


namespace py = pybind11;

// Bind the iphdr struct and make fields read/write
PYBIND11_MODULE(pypcap, m) {

    py::enum_<messagefactory::EtherTypes>(m, "EtherTypes")
        .value("PYPCAP_ETHERTYPE_IP", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_IP)
        .value("PYPCAP_ETHERTYPE_ARP", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_ARP)
        .value("PYPCAP_ETHERTYPE_ETHBRIDGE", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_ETHBRIDGE)
        .value("PYPCAP_ETHERTYPE_REVARP", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_REVARP)
        .value("PYPCAP_ETHERTYPE_AT", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_AT)
        .value("PYPCAP_ETHERTYPE_AARP", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_AARP)
        .value("PYPCAP_ETHERTYPE_VLAN", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_VLAN)
        .value("PYPCAP_ETHERTYPE_IPX", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_IPX)
        .value("PYPCAP_ETHERTYPE_IPV6", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_IPV6)
        .value("PYPCAP_ETHERTYPE_LOOPBACK", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_LOOPBACK)
        .value("PYPCAP_ETHERTYPE_PPPOED", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_PPPOED)
        .value("PYPCAP_ETHERTYPE_PPPOES", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_PPPOES)
        .value("PYPCAP_ETHERTYPE_MPLS", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_MPLS)
        .value("PYPCAP_ETHERTYPE_PPP", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_PPP)
        .value("PYPCAP_ETHERTYPE_ROCEV1", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_ROCEV1)
        .value("PYPCAP_ETHERTYPE_IEEE_802_1AD", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_IEEE_802_1AD)
        .value("PYPCAP_ETHERTYPE_WAKE_ON_LAN", messagefactory::EtherTypes::PYPCAP_ETHERTYPE_WAKE_ON_LAN)
        .export_values();
        
    py::enum_<messagefactory::DhcpMessageType>(m, "DhcpMessageType")
        .value("DHCP_UNKNOWN_MSG_TYPE", messagefactory::DhcpMessageType::DHCP_UNKNOWN_MSG_TYPE)
        .value("DHCP_DISCOVER", messagefactory::DhcpMessageType::DHCP_DISCOVER)
        .value("DHCP_OFFER", messagefactory::DhcpMessageType::DHCP_OFFER)
        .value("DHCP_REQUEST", messagefactory::DhcpMessageType::DHCP_REQUEST)
        .value("DHCP_DECLINE", messagefactory::DhcpMessageType::DHCP_DECLINE)
        .value("DHCP_ACK", messagefactory::DhcpMessageType::DHCP_ACK)
        .value("DHCP_NAK", messagefactory::DhcpMessageType::DHCP_NAK)
        .value("DHCP_RELEASE", messagefactory::DhcpMessageType::DHCP_RELEASE)
        .value("DHCP_INFORM", messagefactory::DhcpMessageType::DHCP_INFORM)
        .export_values();

    py::class_<messagefactory::HeaderEthernet>(m, "EthernetHeader")
        .def(py::init<>())
        .def_property("mac_address_source",
            [](const messagefactory::HeaderEthernet &self) {return self.getSourceMacAddr();},
            [](messagefactory::HeaderEthernet &self, const std::string &value) {self.setSourceMacAddr(value);})
        .def_property("mac_address_destination",
            [](const messagefactory::HeaderEthernet &self) {return self.getDestinationMacAddr();},
            [](messagefactory::HeaderEthernet &self, const std::string &value) {self.setDestinationMacAddr(value);})
        .def_property("ether_type",
            [](const messagefactory::HeaderEthernet &self) {return self.getEtherType();},
            [](messagefactory::HeaderEthernet &self, messagefactory::EtherTypes value) {self.setEtherType(value);});
    
    py::class_<messagefactory::HeaderUdp>(m, "UdpHeader")
        .def(py::init<>())
        .def_property("port_source",
            [](const messagefactory::HeaderUdp &self) {return self.getSourcePort();},
            [](messagefactory::HeaderUdp &self, uint16_t &value) {self.setSourcePort(value);})
        .def_property("port_destination",
            [](const messagefactory::HeaderUdp &self) {return self.getDestinationPort();},
            [](messagefactory::HeaderUdp &self, uint16_t &value) {self.setDestinationPort(value);})
        .def_property("length",
            [](const messagefactory::HeaderUdp &self) {return self.getLength();},
            [](messagefactory::HeaderUdp &self, uint16_t value) {self.setLength(value);})
        .def_property("header_checksum",
            [](const messagefactory::HeaderUdp &self) {return self.getHeaderChecksum();},
            [](messagefactory::HeaderUdp &self, uint16_t value) {self.setHeaderChecksum(value);});

    py::class_<messagefactory::HeaderIPv4>(m, "IPv4Header")
        .def(py::init<>())
        .def_property("internet_header_length",
            [](const messagefactory::HeaderIPv4 &self) { return self.getInternetHeaderLength(); },
            [](messagefactory::HeaderIPv4 &self, uint8_t value) { self.setInternetHeaderLength(value); })
        .def_property("ip_version",
            [](const messagefactory::HeaderIPv4 &self) { return self.getIpVersion(); },
            [](messagefactory::HeaderIPv4 &self, uint8_t value) { self.setIpVersion(value); })
        .def_property("type_of_service",
            [](const messagefactory::HeaderIPv4 &self) { return self.getTypeOfService(); },
            [](messagefactory::HeaderIPv4 &self, uint8_t value) { self.setTypeOfService(value); })
        .def_property("total_length",
            [](const messagefactory::HeaderIPv4 &self) { return self.getTotalLength(); },
            [](messagefactory::HeaderIPv4 &self, uint16_t value) { self.setTotalLength(value); })
        .def_property("ip_id",
            [](const messagefactory::HeaderIPv4 &self) { return self.getIpId(); },
            [](messagefactory::HeaderIPv4 &self, uint16_t value) { self.setIpId(value); })
        .def_property("fragment_offset",
            [](const messagefactory::HeaderIPv4 &self) { return self.getFragmentOffset(); },
            [](messagefactory::HeaderIPv4 &self, uint16_t value) { self.setFragmentOffset(value); })
        .def_property("time_to_live",
            [](const messagefactory::HeaderIPv4 &self) { return self.getTimeToLive(); },
            [](messagefactory::HeaderIPv4 &self, uint8_t value) { self.setTimeToLive(value); })
        .def_property("protocol",
            [](const messagefactory::HeaderIPv4 &self) { return self.getProtocol(); },
            [](messagefactory::HeaderIPv4 &self, uint8_t value) { self.setProtocol(value); })
        .def_property("header_checksum",
            [](const messagefactory::HeaderIPv4 &self) { return self.getHeaderChecksum(); },
            [](messagefactory::HeaderIPv4 &self, uint16_t value) { self.setHeaderChecksum(value); })
        .def_property("source_ip_address",
            [](const messagefactory::HeaderIPv4 &self) { return self.getSrcIPAddress(); },
            [](messagefactory::HeaderIPv4 &self, std::string value) { self.setSrcIPAddress(value); })
        .def_property("destination_ip_address",
            [](const messagefactory::HeaderIPv4 &self) { return self.getDstIPAddress();},
            [](messagefactory::HeaderIPv4 &self, std::string value) { self.setDstIPAddress(value);});
    
    py::class_<messagefactory::HeaderDhcp>(m, "DhcpHeader")
        .def(py::init<>())
        .def_property("op_code",
            [](const messagefactory::HeaderDhcp &self) { return self.getOpCode(); },
            [](messagefactory::HeaderDhcp &self, uint8_t value) { self.setOpCode(value); })
        .def_property("hardware_type",
            [](const messagefactory::HeaderDhcp &self) { return self.getHardwareType(); },
            [](messagefactory::HeaderDhcp &self, uint8_t value) { self.setHardwareType(value); })
        .def_property("hardware_address_length",
            [](const messagefactory::HeaderDhcp &self) { return self.getHardwareAddressLength(); },
            [](messagefactory::HeaderDhcp &self, uint8_t value) { self.setHardwareAddressLength(value); })
        .def_property("hops",
            [](const messagefactory::HeaderDhcp &self) { return self.getHops(); },
            [](messagefactory::HeaderDhcp &self, uint8_t value) { self.setHops(value); })
        .def_property("transaction_id",
            [](const messagefactory::HeaderDhcp &self) { return self.getTransactionID(); },
            [](messagefactory::HeaderDhcp &self, uint32_t value) { self.setTransactionID(value); })
        .def_property("seconds_elapsed",
            [](const messagefactory::HeaderDhcp &self) { return self.getSecondsElapsed(); },
            [](messagefactory::HeaderDhcp &self, uint16_t value) { self.setSecondsElapsed(value); })
        .def_property("flags",
            [](const messagefactory::HeaderDhcp &self) { return self.getFlags(); },
            [](messagefactory::HeaderDhcp &self, uint16_t value) { self.setFlags(value); })
        .def_property("client_ip_address",
            [](const messagefactory::HeaderDhcp &self) { return self.getClientIpAddress(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setClientIpAddress(value); })
        .def_property("your_ip_address",
            [](const messagefactory::HeaderDhcp &self) { return self.getYourIpAddress(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setYourIpAddress(value); })
        .def_property("server_ip_address",
            [](const messagefactory::HeaderDhcp &self) { return self.getServerIpAddress(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setServerIpAddress(value); })
        .def_property("relay_agent_ip_address",
            [](const messagefactory::HeaderDhcp &self) { return self.getRelayAgentIpAddress(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setRelayAgentIpAddress(value); })
        .def_property("client_hardware_address",
            [](const messagefactory::HeaderDhcp &self) { return self.getClientHardwareAddress(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setClientHardwareAddress(value); })
        .def_property("server_name",
            [](const messagefactory::HeaderDhcp &self) { return self.getServerName(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setServerName(value); })
        .def_property("boot_filename",
            [](const messagefactory::HeaderDhcp &self) { return self.getBootFilename(); },
            [](messagefactory::HeaderDhcp &self, const std::string &value) { self.setBootFilename(value); })
        .def_property("magic_number",
            [](const messagefactory::HeaderDhcp &self) { return self.getMagicNumber(); },
            [](messagefactory::HeaderDhcp &self, uint32_t value) { self.setMagicNumber(value); });

    // Expose the DhcpMessage class and bind the getIPv4Header function
    py::class_<messagefactory::DhcpMessage>(m, "DhcpMessage")
        .def(py::init<>())
        .def_property("ethernet_header", 
            [](messagefactory::DhcpMessage &self) -> messagefactory::HeaderEthernet& {return *self.getEthernetHeader();}, 
            [](messagefactory::DhcpMessage &self, const messagefactory::HeaderEthernet& header) {
                messagefactory::HeaderEthernet* current_header = self.getEthernetHeader();
                if (current_header) {*current_header = header;}}
            ,py::return_value_policy::reference_internal)
        .def_property("ipv4_header", 
            [](messagefactory::DhcpMessage &self) -> messagefactory::HeaderIPv4& {return *self.getIPv4Header();}, 
            [](messagefactory::DhcpMessage &self, const messagefactory::HeaderIPv4& header) {
                messagefactory::HeaderIPv4* current_header = self.getIPv4Header();
                if (current_header) {*current_header = header;}}
            ,py::return_value_policy::reference_internal)
        .def_property("udp_header", 
            [](messagefactory::DhcpMessage &self) -> messagefactory::HeaderUdp& {return *self.getUdpHeader();}, 
            [](messagefactory::DhcpMessage &self, const messagefactory::HeaderUdp& header) {
                messagefactory::HeaderUdp* current_header = self.getUdpHeader();
                if (current_header) {*current_header = header;}}
            ,py::return_value_policy::reference_internal)
        .def_property("dhcp_header", 
            [](messagefactory::DhcpMessage &self) -> messagefactory::HeaderDhcp& {return *self.getDhcpHeader();}, 
            [](messagefactory::DhcpMessage &self, const messagefactory::HeaderDhcp& header) {
                messagefactory::HeaderDhcp* current_header = self.getDhcpHeader();
                if (current_header) {*current_header = header;}}
            ,py::return_value_policy::reference_internal)
        .def("send", 
        [](messagefactory::DhcpMessage &self, std::string interface_name){ self.send(interface_name);})
        
        .def("add_option", 
        [](messagefactory::DhcpMessage &self, int option, std::vector<uint8_t> data){ self.addOption(option, data);})
        
        .def("has_option", 
        [](messagefactory::DhcpMessage &self, int option){ return self.hasOption(option);})
        
        .def("get_option_data", 
        [](messagefactory::DhcpMessage &self, int option){ return self.getOptionData(option);})
        
        .def("set_all_bytes", [](messagefactory::DhcpMessage &self, py::object data) {
            py::buffer_info bufInfo;
            try {
                bufInfo = data.cast<py::buffer>().request();
            } catch (const std::exception& e) {
                throw std::invalid_argument("Input must be a bytes-like object: " + std::string(e.what()));
            }
            if (bufInfo.ndim != 1) {
                throw std::invalid_argument("Input must be a one-dimensional bytes-like object.");
            }
            self.setAllBytes(static_cast<uint8_t*>(bufInfo.ptr), bufInfo.size);
        })
        .def("print_packet_as_bytes_stream", 
        [](messagefactory::DhcpMessage &self){ self.printRawPacketAsByteStream();})
        
        .def("print_payload_as_bytes_stream", 
        [](messagefactory::DhcpMessage &self){ self.printPayloadAsByteStream();})
        
        .def("get_all_bytes", [](messagefactory::DhcpMessage& self) -> pybind11::bytes {
            const uint8_t* data = self.getAllBytes().data();
            int size = self.getAllBytes().size();

            return pybind11::bytes(reinterpret_cast<const char*>(data), size);
        })
        .def("get_bytes", [](messagefactory::DhcpMessage& self) -> pybind11::bytes {
            const uint8_t* data = self.getBytes().data();
            int size = self.getBytes().size();

            return pybind11::bytes(reinterpret_cast<const char*>(data), size);
        })
        .def_property("message_type",
        [](messagefactory::DhcpMessage &self) { return static_cast<messagefactory::DhcpMessageType>(self.getMessageType());},
        [](messagefactory::DhcpMessage &self, messagefactory::DhcpMessageType msgType) { self.setMessageType(static_cast<pcpp::DhcpMessageType>(msgType)); })
        
        .def_property("compute_before_send",
        [](messagefactory::DhcpMessage &self) { return self.getComputeBeforeSend();},
        [](messagefactory::DhcpMessage &self, bool op) { self.setComputeBeforeSend(op);})
    
        .def("__repr__", [](const messagefactory::DhcpMessage &msg) {
            return "<DhcpMessage>";
        });

    py::class_<messagefactory::EthernetMessage>(m, "EthernetMessage")
        .def(py::init<>())
        .def_property("ethernet_header",
        [](messagefactory::EthernetMessage &self) -> messagefactory::HeaderEthernet& {return *self.getEthernetHeader();},
        [](messagefactory::EthernetMessage &self, const messagefactory::HeaderEthernet& header) {
                messagefactory::HeaderEthernet* current_header = self.getEthernetHeader();
                if (current_header) {*current_header = header;}}
            ,py::return_value_policy::reference_internal)
        
        .def("send", &messagefactory::EthernetMessage::send, py::arg("interface_name"))
        .def("set_all_bytes", [](messagefactory::EthernetMessage &self, py::object data) {
            py::buffer_info bufInfo;
            try {
                bufInfo = data.cast<py::buffer>().request();
            } catch (const std::exception& e) {
                throw std::invalid_argument("Input must be a bytes-like object: " + std::string(e.what()));
            }
            if (bufInfo.ndim != 1) {
                throw std::invalid_argument("Input must be a one-dimensional bytes-like object.");
            }
            self.setAllBytes(static_cast<uint8_t*>(bufInfo.ptr), bufInfo.size);
        })
        .def("get_all_bytes", [](messagefactory::EthernetMessage& self) -> pybind11::bytes {
            const uint8_t* data = self.getAllBytes().data();
            int size = self.getAllBytes().size();

            return pybind11::bytes(reinterpret_cast<const char*>(data), size);
        })
        .def("__repr__", [](const messagefactory::EthernetMessage &msg) {
            return "<EthernetMessage>";
        });
}
