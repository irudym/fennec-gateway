cmake_minimum_required(VERSION 2.8)
project(fennecGateway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories("../iotivity-1.1.0/resource/include" "../iotivity-1.1.0/resource/csdk/stack/include" "../iotivity-1.1.0/resource/c_common")
include_directories("../iotivity-1.1.0/resource/csdk/security/include" "../iotivity-1.1.0/resource/csdk/connectivity/inc" "../iotivity-1.1.0/resource/oc_logger/include")

link_directories("~/dev/iotivity-1.1.0/out/linux/x86_64/release")

set(SOURCE_FILES main.cpp GatewayClient.cpp GatewayClient.h TemperatureSensor.cpp TemperatureSensor.h)
add_executable(fennec_gtw ${SOURCE_FILES})

target_link_libraries(fennec_gtw oc octbstack logger coap c_common ocsrm )
