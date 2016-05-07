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

using namespace std;
using namespace OC;

/*
 * Description: Temprature sensor class
 */
class TemperatureSensor {
    shared_ptr<OCResource> m_resourceHandle;
    OCRepresentation m_temperatureRepresentation;
    GetCallback m_GETCallback;
    void onGet(const HeaderOptions&, const OCRepresentation&, int);
    bool m_isObserved;
    //void onObserve(const HeaderOptions headerOptions, const OCRepresentation& rep, int eCode,
    //               int sequenceNumber);

public:
    void get();
    //void startObserve();
    //void stopObserve();
    TemperatureSensor(shared_ptr<OCResource> Resource);
    virtual ~TemperatureSensor();
};


#endif //FENNECGATEWAY_TEMPERATURESENSOR_H
