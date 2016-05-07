//
// Created by Igor on 07/05/16.
//

#include "GatewayClient.h"
#include "../iotivity-weeder/namedefs.h"

#include "TemperatureSensor.h"
#include "MoistSensor.h"

static const char* SVR_DB_FILE_NAME = "./fennec_db_client.dat";

static FILE* client_open(const char* /*path*/, const char *mode)
{
    return fopen(SVR_DB_FILE_NAME, mode);
}

GatewayClient::GatewayClient() {
    cout << "Initializing Fennec Gateway" << endl;
    initializePlatform();
}

GatewayClient::~GatewayClient() {

}

void GatewayClient::initializePlatform() {
    OCPersistentStorage ps {client_open, fread, fwrite, fclose, unlink };

    m_platformConfig = make_shared<PlatformConfig>(ServiceType::InProc, ModeType::Client, "0.0.0.0",
                                                   0, OC::QualityOfService::HighQos);
    OCPlatform::Configure(*m_platformConfig);
    m_resourceDiscoveryCallback = bind(&GatewayClient::discoveredResource, this, placeholders::_1);
}

void GatewayClient::discoveredResource(shared_ptr<OCResource> Resource) {
    try {
        if(Resource) {
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
                data_sensor = make_shared<TemperatureSensor>(Resource);

                //TODO: the same as block below
                if(m_mSensors.find(Resource->uri()) != m_mSensors.end()) {
                    //Add resource to the resource map hash
                    m_mSensors[Resource->uri()] = data_sensor;
                    data_sensor->get();
                } else {
                    //the resrouce already in data set
                    cout << "Resource " << Resource->uri() << "already in data set" <<endl;
                }

            } else if (resourceUri == MOIST1_RESOURCE_ENDPOINT || resourceUri == MOIST2_RESOURCE_ENDPOINT){
                cout << "Found moist sensor" << endl;
                data_sensor = make_shared<MoistSensor>(Resource);

                //TODO: the same as block above
                if(m_mSensors.find(Resource->uri()) != m_mSensors.end()) {
                    //Add resource to the resource map hash
                    m_mSensors[Resource->uri()] = data_sensor;
                    data_sensor->get();
                } else {
                    //the resrouce already in data set
                    cout << "Resource " << Resource->uri() << "already in data set" <<endl;
                }
            }

        }
    } catch (OCException& ex)
    {
        cerr << "Caught exception in discoveredResource: " << ex.reason() << endl;
    }
}

OCStackResult GatewayClient::findResource() {
    int amount_of_resources = 0;
    string coap_multicast_discovery = string(OC_RSRVD_WELL_KNOWN_URI);
    return OCPlatform::findResource("", coap_multicast_discovery.c_str(),  CT_DEFAULT, m_resourceDiscoveryCallback,
                             OC::QualityOfService::LowQos);
}

TResourceMap GatewayClient::getResources() {
    return m_mSensors;
}








