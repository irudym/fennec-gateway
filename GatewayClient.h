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

using namespace OC;
using namespace std;

typedef map<string, shared_ptr<SensorResource>> TResourceMap;
class GatewayClient {
    shared_ptr<PlatformConfig> m_platformConfig; //platform configuration
    FindCallback m_resourceDiscoveryCallback;    //callback binding
    TResourceMap m_mSensors;

public:
    GatewayClient();
    virtual ~GatewayClient();
    OCStackResult findResource();

    TResourceMap getResources();

private:
    void initializePlatform();
    void discoveredResource(shared_ptr<OCResource> Resource);
};


#endif //FENNECGATEWAY_GATEWAYCLIENT_H
