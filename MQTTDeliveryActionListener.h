//
// Created by ubuntu on 23.05.16.
//

#ifndef FENNECGATEWAY_MQTTDELIVERYACTIONLISTENER_H
#define FENNECGATEWAY_MQTTDELIVERYACTIONLISTENER_H

#include <iostream>
#include <string>
#include "MQTTActiveListener.h"
#include "mqtt/async_client.h"

class MQTTDeliveryActionListener :public MQTTActiveListener {
    bool done_;

    virtual void on_failure(const mqtt::itoken& tok) {
        on_failure(tok);
        done_ = true;
    }

    virtual void on_success(const mqtt::itoken& tok) {
        on_success(tok);
        done_ = true;
    }

public:
    MQTTDeliveryActionListener() : done_(false) {}
    bool is_done() const { return done_; }
};


#endif //FENNECGATEWAY_MQTTDELIVERYACTIONLISTENER_H
