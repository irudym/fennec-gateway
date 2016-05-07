//
// Created by Igor on 07/05/16.
//

#include "GatewayClient.h"
#include "../iotivity-weeder/namedefs.h"


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

            cout << "\nFound Resource" << endl << "Resource Types:" << endl;
            for (auto& resourceTypes : Resource->getResourceTypes())
            {
                cout << "\t" << resourceTypes << endl;
            }

            cout << "Resource Interfaces: " << endl;
            for (auto& resourceInterfaces : Resource->getResourceInterfaces())
            {
                cout << "\t" << resourceInterfaces << endl;
            }

            cout << "Resource uri: " << resourceUri << endl;
            cout << "host: " << hostAddress << endl;
            /*
            if (resourceUri == TEMPERATURE_RESOURCE_ENDPOINT)
            {
                m_temperatureSensor = make_shared<TemperatureSensor>(Resource);
            }
            else if (resourceUri == LIGHT_RESOURCE_ENDPOINT)
            {
                m_ambientLightSensor = make_shared<AmbientLight>(Resource);
            }
            else if (resourceUri == LED_RESOURCE_ENDPOINT)
            {
                m_platformLED = make_shared<LED>(Resource);
            }
            */
        }
    } catch (OCException& ex)
    {
        cerr << "Caught exception in discoveredResource: " << ex.reason() << endl;
    }
}

OCStackResult GatewayClient::findResource() {
    int amount_of_resources = 0;
    string coap_multicast_discovery = string(OC_RSRVD_WELL_KNOWN_URI "?if=" EDISON_RESOURCE_INTERFACE);
    return OCPlatform::findResource("", coap_multicast_discovery.c_str(),  CT_DEFAULT, m_resourceDiscoveryCallback,
                             OC::QualityOfService::LowQos);
}






