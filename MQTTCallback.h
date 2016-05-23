//
// Created by ubuntu on 23.05.16.
//

#ifndef FENNECGATEWAY_MQTTCALLBACK_H
#define FENNECGATEWAY_MQTTCALLBACK_H

#include <iostream>
#include <string>
#include "mqtt/async_client.h"

using namespace std;

class MQTTCallback : public virtual mqtt::callback {
public:
    virtual void connection_lost(const string& cause) {
        cout << "\nConnection lost" << endl;
        if (!cause.empty())
            cout << "\tcause: " << cause << endl;
    }

    // We're not subscribed to anything, so this should never be called.
    virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg) {}

    virtual void delivery_complete(mqtt::idelivery_token_ptr tok) {
        cout << "Delivery complete for token: "
        << (tok ? tok->get_message_id() : -1) << std::endl;
    }
};


#endif //FENNECGATEWAY_MQTTCALLBACK_H
