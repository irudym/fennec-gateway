//
// Created by Igor on 07/05/16.
//

#ifndef FENNECGATEWAY_SENSORRESOURCE_H
#define FENNECGATEWAY_SENSORRESOURCE_H

#include <string>
#include <iostream>
#include <memory>
#include "ocstack.h"
#include "OCApi.h"
#include "OCPlatform.h"
#include "OCResource.h"
#include "mqtt/async_client.h"

using namespace std;
using namespace OC;

/*
 * Abstract class which describe OIC resource methods
 */

class SensorResource {
protected:
    shared_ptr<OCResource> m_resourceHandle;

    GetCallback m_GETCallback;
    ObserveCallback m_OBSERVECallback;
    shared_ptr<mqtt::async_client> m_MqttClient;
    string m_MqttTopic;

    virtual void onGet(const HeaderOptions&, const OCRepresentation&, int) = 0;
    bool m_isObserved;
    virtual void onObserve(const HeaderOptions headerOptions, const OCRepresentation& rep, int eCode, int sequenceNumber) = 0;

public:
    virtual void get() = 0;
    virtual void startObserve() = 0;
    virtual void stopObserve() = 0;

    shared_ptr<OCResource> getDescription() { return m_resourceHandle; }
};


#endif //FENNECGATEWAY_SENSORRESOURCE_H
