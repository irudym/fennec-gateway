//
// Created by Igor Rudym on 23/04/16.
// Copyright 2016 Igor Rudym
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/**
 * Description: Fennec Gateway - a service which collects data over OIC standart and send it to
 * a cloud server over MQTT protocol
 * MQTT allows to share data through NAT connectio as the gateway intiates the connection
 */
#include <iostream>
#include <signal.h>
#include <cstring>
#include <map>
#include <cstdlib>
#include <pthread.h>
#include <mutex>
#include <condition_variable>


#include "GatewayClient.h"

#define _VERSION "0.1"

using namespace std;

int main(int argc, char *argv[]) {
    cout<< "Fennec Gateway v" << _VERSION << endl;
    if(argc>1) {
        if(!strcmp(argv[1], "--help")) {
            //show usage information
            cout << "\nUsage: " << endl;
            cout << "fennec_gtw [options]" << endl;
            cout << "\t--help       Show this information" << endl;
            cout << "\t--show       Get data from all devices and show it" << endl;
        }
        return 0;
    }
    GatewayClient gateway("fennec.tech:1883","fennec_gateway_01234");

    try {
        int r_amount = 0;
        //find all four resources (2x temp, 2x moist)
        for(int i=0;i<2;i++)
        {
            OCStackResult res = gateway.findResource();
            if (res == OC_STACK_OK) {
                //cout << "OK!" << endl;
                r_amount = gateway.getResources().size();
            } else {
                cout << "Failed: " << res << endl;
            }
            usleep(5000);
            //r_amount++;
        } //while (r_amount < 4);

        cout <<"OK! Found " << r_amount << "resources." << endl;

        // A condition variable will free the mutex it is given, then do a non-
        // intensive block until 'notify' is called on it.  In this case, since we
        // don't ever call cv.notify, this should be a non-processor intensive version
        // of while(true);
        std::mutex blocker;
        std::condition_variable cv;
        std::unique_lock<std::mutex> lock(blocker);
        cv.wait(lock);
    } catch (OCException& e) {
        cout << "Exception in main: "<<e.what();
    }

    return 0;
}
