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

#include "TemperatureSensor.h"

using namespace OC;
using namespace std;

class GatewayClient {
    shared_ptr<PlatformConfig> m_platformConfig; //platform configuration
    FindCallback m_resourceDiscoveryCallback;    //callback binding

public:
    GatewayClient();
    virtual ~GatewayClient();
    OCStackResult findResource();

private:
    void initializePlatform();
    void discoveredResource(shared_ptr<OCResource> Resource);
};


#endif //FENNECGATEWAY_GATEWAYCLIENT_H
