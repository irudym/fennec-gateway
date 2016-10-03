YOCTOCXXFLAGS=-I$(PKG_CONFIG_SYSROOT_DIR)/usr/include/iotivity/resource/ -I$(PKG_CONFIG_SYSROOT_DIR)/usr/include/iotivity/resource/stack -I$(PKG_CONFIG_SYSROOT_DIR)/usr/include/iotivity/resource/ocrandom -I$(PKG_CONFIG_SYSROOT_DIR)/usr/include/iotivity/resource/logger -I$(PKG_CONFIG_SYSROOT_DIR)/usr/include/iotivity/resource/oc_logger

YOCTOLDFLAGS=-loc -loctbstack -loc_logger -lmraa -lpthread -lcoap -lmqttpp -lpaho-mqtt3a

all: fennec_gtw

%.o: %.cpp
ifeq ($(PKG_CONFIG_SYSROOT_DIR),)
	echo "Error: Yocto cross-toolchain environment not initialized"
	exit 1
endif
	$(CXX) -std=c++0x -c -o $@ $< $(YOCTOCXXFLAGS)

fennec_gtw: main.o GatewayClient.o MoistSensor.o TemperatureSensor.o MQTTActiveListener.o MQTTCallback.o MQTTDeliveryActionListener.o 
	$(CXX) -o weeder main.o weederServer.o CSensor.o MoistSensor.o TemperatureSensor.o WeederObserver.o $(YOCTOLDFLAGS)

clean:
	rm -rf fennec_gtw *.o
	
