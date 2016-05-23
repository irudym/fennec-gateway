//
// Created by Igor on 07/05/16.
//

#include "GatewayClient.h"
#include "../iotivity-weeder/namedefs.h"

#include "TemperatureSensor.h"
#include "MoistSensor.h"

#define _DEBUG_

static const char* SVR_DB_FILE_NAME = "./fennec_db_client.dat";

static FILE* client_open(const char* /*path*/, const char *mode)
{
    return fopen(SVR_DB_FILE_NAME, mode);
}

GatewayClient::GatewayClient(string mqtt_server, string client_id) {
    cout << "Initializing Fennec Gateway" << endl;
    initializePlatform();

    //setup MQTT
    m_MqttClient = make_shared<mqtt::async_client>(mqtt_server, client_id);
    m_MqttClient->set_callback(m_MqttCallback);

    m_MqttTopic = "IOT/fennec:1234567890/data";

    //connect to the MQTT server
    try {
        mqtt::itoken_ptr conntok = m_MqttClient->connect();
        std::cout << "Waiting for the connection..." << std::flush;
        conntok->wait_for_completion();
        std::cout << "OK" << std::endl;
    } catch(const mqtt::exception& exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
    }

}

GatewayClient::~GatewayClient() {

}

void GatewayClient::initializePlatform() {
    OCPersistentStorage ps {client_open, fread, fwrite, fclose, unlink };

    m_platformConfig = make_shared<PlatformConfig>(ServiceType::InProc, ModeType::Client, "0.0.0.0",
                                                  0, OC::QualityOfService::HighQos);

    //m_platformConfig = make_shared<PlatformConfig>(ServiceType::InProc, ModeType::Client, CT_DEFAULT, CT_DEFAULT,
    //                        OC::QualityOfService::HighQos);
    
    OCPlatform::Configure(*m_platformConfig);
    m_resourceDiscoveryCallback = bind(&GatewayClient::discoveredResource, this, placeholders::_1);
}

void GatewayClient::discoveredResource(shared_ptr<OCResource> Resource) {

    //DEBUG:
#ifdef _DEBUG_
    cout << "Get response!" << endl;
    if(Resource) {
        cout <<"DEBUG: found resource:" <<endl;
        cout <<"\tURI: " << Resource->uri() << endl;
        cout <<"\tHost: " << Resource->host() << endl;
        cout <<"\tResources types:" << endl;
        for (auto& resourceTypes : Resource->getResourceTypes())
        {
            cout << "\t\t" << resourceTypes << endl;
        }
    }
#endif


    try {
        if(Resource) {

            std::lock_guard<std::mutex> lock(curResourceLock);


            string resourceUri = Resource->uri();
            string hostAddress = Resource->host();

            //cout << "\nFound Resource" << endl << "Resource Types:" << endl;
            for (auto& resourceTypes : Resource->getResourceTypes())
            {
                //cout << "\t" << resourceTypes << endl;
            }

            //cout << "Resource Interfaces: " << endl;
            for (auto& resourceInterfaces : Resource->getResourceInterfaces())
            {
                //cout << "\t" << resourceInterfaces << endl;
            }

            shared_ptr<SensorResource> data_sensor(nullptr);


            if (resourceUri == TEMPERATURE1_RESOURCE_ENDPOINT || resourceUri == TEMPERATURE2_RESOURCE_ENDPOINT) {
                cout << "Found temperature sensor" << endl;
                string topic = "IOT/fennec1:fennec1/data";
                if(resourceUri == TEMPERATURE2_RESOURCE_ENDPOINT) topic = "IOT/fennec2:fennec2/data";
                data_sensor = make_shared<TemperatureSensor>(Resource, m_MqttClient, topic);


                //TODO: the same as block below
                if(m_mSensors.find(Resource->uniqueIdentifier()) == m_mSensors.end()) {
                    //Add resource to the resource map hash
                    m_mSensors[Resource->uniqueIdentifier()] = data_sensor;
                    data_sensor->get();
                    // start observing
                    data_sensor->startObserve();
                } else {
                    //the resource already in data set
                    cout << "Resource " << Resource->uri() << " already in data set" <<endl;
                }

            } else if (resourceUri == MOIST1_RESOURCE_ENDPOINT || resourceUri == MOIST2_RESOURCE_ENDPOINT){
                cout << "Found moist sensor" << endl;

                string topic = "IOT/fennec1:fennec1/data";
                if(resourceUri == MOIST2_RESOURCE_ENDPOINT) topic = "IOT/fennec2:fennec2/data";
                data_sensor = make_shared<MoistSensor>(Resource, m_MqttClient,topic);

                //TODO: the same as block above
                if(m_mSensors.find(Resource->uniqueIdentifier()) == m_mSensors.end()) {
                    //Add resource to the resource map hash
                    m_mSensors[Resource->uniqueIdentifier()] = data_sensor;
                    data_sensor->get();
                    data_sensor->startObserve();
                } else {
                    //the resource is already in data set
                    cout << "Resource " << Resource->uri() << " already in data set" <<endl;
                }
            }

        }
    } catch (OCException& ex)
    {
        cerr << "Caught exception in discoveredResource: " << ex.reason() << endl;
    }
}

OCStackResult GatewayClient::findResource() {
    string coap_multicast_discovery = string(OC_RSRVD_WELL_KNOWN_URI);
    //perform multicast search of all resources
    return OCPlatform::findResource("", coap_multicast_discovery.c_str(),  CT_DEFAULT, m_resourceDiscoveryCallback,
                             OC::QualityOfService::LowQos);
}

TResourceMap GatewayClient::getResources() {
    return m_mSensors;
}








