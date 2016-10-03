//
// Created by Igor on 07/05/16.
//

#include "TemperatureSensor.h"
#include "../iotivity-weeder/namedefs.h"


TemperatureSensor::TemperatureSensor(shared_ptr<OCResource> Resource, shared_ptr<mqtt::async_client> mqtt_client, string topic) {
    m_isObserved = false;
    m_resourceHandle = Resource;
    m_MqttClient = mqtt_client;
    m_MqttTopic = topic;

    cout << "Added sensor: " << Resource->uri() << endl;

    m_GETCallback = bind(&TemperatureSensor::onGet, this, placeholders::_1, placeholders::_2, placeholders::_3);
    m_OBSERVECallback = bind(&TemperatureSensor::onObserve, this, placeholders::_1,
                             placeholders::_2, placeholders::_3, placeholders::_4);
}

TemperatureSensor::~TemperatureSensor() {
}

void TemperatureSensor::get() {
    QueryParamsMap params;
    m_resourceHandle->get(params, m_GETCallback);
}

void TemperatureSensor::onGet(const HeaderOptions &headerOptions, const OCRepresentation &representation, int errCode) {
    if(errCode == OC_STACK_OK) {
        double value;
        representation.getValue(TEMPERATURE_RESOURCE_KEY, value);
        cout << "Current temperature reading in Celsius: " << value << endl;

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

void TemperatureSensor::onObserve(const HeaderOptions headerOptions, const OCRepresentation &rep, int eCode,
                                  int sequenceNumber) {
    try {
        if (eCode == OC_STACK_OK && sequenceNumber != OC_OBSERVE_NO_OPTION)
        {
            if(sequenceNumber == OC_OBSERVE_REGISTER)
            {
                //cout << "Observe registration action is successful" << endl;
            }
            else if(sequenceNumber == OC_OBSERVE_DEREGISTER)
            {
                //cout << "Observe De-registration action is successful" << endl;
            }
            double value;
            rep.getValue(TEMPERATURE_RESOURCE_KEY, value);
            cout << "["<< sequenceNumber <<"]::" << "Observing " << m_resourceHandle->uri() << ": Current temperature reading in Celsius is " << value << endl;

            auto value_str = std::to_string(value-15);
            mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>("{\"d\":{\"temperature\":" + value_str + "}}");
            pubmsg->set_qos(1);
            m_MqttClient->publish(m_MqttTopic, pubmsg)->wait_for_completion(10000L);
            std::cout << "OK" << std::endl;
        }
        else
        {
            if(sequenceNumber == OC_OBSERVE_NO_OPTION)
            {
                cerr << "Observe registration or de-registration action is failed" << endl;
            }
            else
            {
                cerr << "TemperatureSensor: Observer response error" << endl;
            }
        }
    } catch (std::exception& e)
    {
        std::cout << "[TemperatureSensor]::Exception: " << e.what() << " in onObserve" << std::endl;
    }
}

void TemperatureSensor::startObserve() {
    cout << "[TemperatureSensor]::startObserver() for " << m_resourceHandle->uri() << endl;
    if (!m_isObserved)
    {
        cout << "\tStarting observing temperature sensor" << endl;
        m_resourceHandle->observe(ObserveType::Observe, QueryParamsMap(), m_OBSERVECallback);
    }
    m_isObserved = true;
}

void TemperatureSensor::stopObserve() {
    if (m_isObserved)
    {
        m_resourceHandle->cancelObserve();
        cout << "\tStopped observing temperature sensor" << endl;
    }
    m_isObserved = false;
}













