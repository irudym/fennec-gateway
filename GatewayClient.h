//
// Created by Igor Rudym on 07/05/16.
//

#ifndef FENNECGATEWAY_GATEWAYCLIENT_H
#define FENNECGATEWAY_GATEWAYCLIENT_H

#include <string>
#include <iostream>
#include <memory>
#include "ocstack.h"
#include "OCApi.h"
#include "OCPlatform.h"
#include "OCResource.h"

#include "SensorResource.h"
#include "TemperatureSensor.h"

#include "MQTTCallback.h"
#include "MQTTDeliveryActionListener.h"

using namespace OC;
using namespace std;

typedef map<OCResourceIdentifier, shared_ptr<SensorResource>> TResourceMap;

class GatewayClient {
    shared_ptr<PlatformConfig> m_platformConfig; //platform configuration
    FindCallback m_resourceDiscoveryCallback;    //callback binding
    TResourceMap m_mSensors;

    std::mutex curResourceLock;
    std::shared_ptr<OCResource> curResource;

    const static ObserveType OBSERVE_TYPE_TO_USE = ObserveType::Observe;
    ObservationIds m_interestedObservers;

    MQTTCallback m_MqttCallback;
    shared_ptr<mqtt::async_client> m_MqttClient;
    string m_MqttTopic;

public:
    GatewayClient(string mqtt_server, string client_id);
    virtual ~GatewayClient();
    OCStackResult findResource();

    TResourceMap getResources();

private:
    void initializePlatform();
    void discoveredResource(shared_ptr<OCResource> Resource);
};


#endif //FENNECGATEWAY_GATEWAYCLIENT_H
