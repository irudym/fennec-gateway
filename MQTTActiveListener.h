//
// Created by ubuntu on 23.05.16.
//

#ifndef FENNECGATEWAY_MQTTACTIVELISTENER_H
#define FENNECGATEWAY_MQTTACTIVELISTENER_H

#include <iostream>
#include <string>
#include "mqtt/async_client.h"

using namespace std;

class MQTTActiveListener :public virtual mqtt::iaction_listener {
protected:
    virtual void on_failure(const mqtt::itoken& tok) {
        cout << "\n\tListener: Failure on token: "
        << tok.get_message_id() << std::endl;
    }

    virtual void on_success(const mqtt::itoken& tok) {
        cout << "\n\tListener: Success on token: "
        << tok.get_message_id() << std::endl;
    }
};


#endif //FENNECGATEWAY_MQTTACTIVELISTENER_H
