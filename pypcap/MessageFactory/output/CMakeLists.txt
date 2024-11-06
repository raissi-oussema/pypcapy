cmake_minimum_required(VERSION 3.9)
project(pypcap)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find Python3 and pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)  
find_package(pybind11 REQUIRED)

# Specify where PcapPlusPlus headers and libraries are located
include_directories(/usr/local/include/pcapplusplus)
include_directories(./include)

# Specify the source files (bindings and EthernetMessage implementation)
set(SOURCE_FILES
    /home/oussema/Desktop/build/MyFolder/pypcap/MessageFactory/src/EthernetMessage.cpp
    /home/oussema/Desktop/build/MyFolder/pypcap/MessageFactory/src/DhcpMessage.cpp
    /home/oussema/Desktop/build/MyFolder/pypcap/MessageFactory/src/IMessageBasic.cpp
    bindings.cpp  # Your pybind11 bindings file
)

# Create the pybind11 extension module (will generate a .so file)
pybind11_add_module(pypcap ${SOURCE_FILES})

# Link the required PcapPlusPlus libraries
target_link_libraries(pypcap PRIVATE Pcap++ Packet++ Common++ pcap pthread)

# Set the output directory for the compiled module
set_target_properties(pypcap PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add an executable (to run a C++ executable in Linux)
add_executable(pypcap_executable main.cpp 
    /home/oussema/Desktop/build/MyFolder/pypcap/MessageFactory/src/EthernetMessage.cpp
    /home/oussema/Desktop/build/MyFolder/pypcap/MessageFactory/src/DhcpMessage.cpp  
    /home/oussema/Desktop/build/MyFolder/pypcap/MessageFactory/src/IMessageBasic.cpp# Add the EthernetMessage source file here
)

# Link the PcapPlusPlus libraries to the executable
target_link_libraries(pypcap_executable PRIVATE Pcap++ Packet++ Common++ pcap)

# Set the output directory for the executable
set_target_properties(pypcap_executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
set(CMAKE_CXX_FLAGS "-g -O0")
target_compile_options(pypcap_executable PRIVATE
    $<$<CONFIG:Debug>:-g -O0>
)