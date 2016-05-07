//
// Created by Igor on 07/05/16.
//

#include "MoistSensor.h"
#include "../iotivity-weeder/namedefs.h"

void MoistSensor::onGet(const HeaderOptions &headerOptions, const OCRepresentation &representation, int errCode) {
    if(errCode == OC_STACK_OK) {
        double value;
        representation.getValue(MOIST_RESOURCE_KEY, value);
        cout << "Current moist level in %: " << value << endl;

        cout << "Sensor information: " << endl;
        cout << "\tURI: " << m_resourceHandle->uri() << "\n\tSID: " << m_resourceHandle->sid() << "\n\tHost: " << m_resourceHandle->host() << endl;
        vector<string> intrf = m_resourceHandle->getResourceInterfaces();
        cout << "\tInterfaces: " << endl;
        for(int i=0; i< intrf.size();i++) cout << "\t\t" << intrf[i] << endl;

        vector<string> types = m_resourceHandle->getResourceTypes();
        cout << "\tTypes: " << endl;
        for(int i=0; i< types.size();i++) cout << "\t\t" << types[i] << endl;
    } else {
        cerr << endl << "Error in GET response from temperature sensor resource" << endl;
    }
}

MoistSensor::MoistSensor(shared_ptr<OCResource> Resource) {
    m_isObserved = false;
    m_resourceHandle = Resource;

    cout << "Added sensor: " << Resource->uri() << endl;

    m_GETCallback = bind(&MoistSensor::onGet, this, placeholders::_1, placeholders::_2, placeholders::_3);
    //m_OBSERVECallback = bind(&TemperatureSensor::onObserve, this, placeholders::_1,
    //                         placeholders::_2, placeholders::_3, placeholders::_4);
}

MoistSensor::~MoistSensor() {

}

void MoistSensor::onObserve(const HeaderOptions headerOptions, const OCRepresentation &rep, int eCode,
                            int sequenceNumber)
{

}

void MoistSensor::get() {
    QueryParamsMap params;
    m_resourceHandle->get(params, m_GETCallback);
}








