//
// Created by Igor Rudym on 07/05/16.
//

#ifndef FENNECGATEWAY_TEMPERATURESENSOR_H
#define FENNECGATEWAY_TEMPERATURESENSOR_H

#include <string>
#include <iostream>
#include <memory>
#include "ocstack.h"
#include "OCApi.h"
#include "OCPlatform.h"
#include "OCResource.h"

#include "SensorResource.h"

using namespace std;
using namespace OC;

/*
 * Description: Temprature sensor class
 */
class TemperatureSensor : public SensorResource {
    OCRepresentation m_temperatureRepresentation;
protected:
    virtual void onGet(const HeaderOptions&, const OCRepresentation&, int);
    virtual void onObserve(const HeaderOptions headerOptions, const OCRepresentation& rep, int eCode, int sequenceNumber);

public:

    virtual void get();

    virtual void startObserve();
    virtual void stopObserve();

    TemperatureSensor(shared_ptr<OCResource> Resource, shared_ptr<mqtt::async_client> m_MqttClient, string);
    virtual ~TemperatureSensor();
};


#endif //FENNECGATEWAY_TEMPERATURESENSOR_H
