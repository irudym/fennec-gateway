cmake_minimum_required(VERSION 2.8)
project(fennecGateway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories("../iotivity-1.1.0/resource/include" "../iotivity-1.1.0/resource/csdk/stack/include" "../iotivity-1.1.0/resource/c_common")
include_directories("../iotivity-1.1.0/resource/csdk/security/include" "../iotivity-1.1.0/resource/csdk/connectivity/inc" "../iotivity-1.1.0/resource/oc_logger/include")
include_directories("../paho.mqtt.cpp/src")
link_directories("~/development/iotivity-1.1.0/out/linux/x86_64/release")

set(SOURCE_FILES main.cpp GatewayClient.cpp GatewayClient.h TemperatureSensor.cpp TemperatureSensor.h SensorResource.h MoistSensor.cpp MoistSensor.h MQTTCallback.cpp MQTTCallback.h MQTTActiveListener.cpp MQTTActiveListener.h MQTTDeliveryActionListener.cpp MQTTDeliveryActionListener.h)
add_executable(fennec_gtw ${SOURCE_FILES} MQTTCallback.cpp MQTTCallback.h MQTTActiveListener.cpp MQTTActiveListener.h MQTTDeliveryActionListener.cpp MQTTDeliveryActionListener.h)

target_link_libraries(fennec_gtw oc octbstack logger coap c_common ocsrm mqttpp mqttv3a)
