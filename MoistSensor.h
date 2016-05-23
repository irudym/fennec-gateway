//
// Created by Igor on 07/05/16.
//

#ifndef FENNECGATEWAY_MOISTSENSOR_H
#define FENNECGATEWAY_MOISTSENSOR_H

#include "SensorResource.h"

#include "MQTTAsync.h"

class MoistSensor : public SensorResource {
    OCRepresentation m_moistRepresentation;
protected:
    virtual void onGet(const HeaderOptions&, const OCRepresentation&, int);
    virtual void onObserve(const HeaderOptions headerOptions, const OCRepresentation& rep, int eCode, int sequenceNumber);

public:
    virtual void get();

    MoistSensor(shared_ptr<OCResource> Resource, shared_ptr<mqtt::async_client> mqtt_client, string);
    virtual ~MoistSensor();

    virtual void startObserve();
    virtual void stopObserve();

};


#endif //FENNECGATEWAY_MOISTSENSOR_H
