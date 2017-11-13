/**
 * Basic manager for wifi and other networks
 */
#pragma once

#include <string>
#include <vector>

#include "Network.h"


using std::string;
using std::vector;


namespace Orza { namespace Network {


class Manager {

    public:

        Manager();

        vector<Network*> getNetworks();

        vector<string> getNetworkSSIDs();

        void connect( string ssid, string pass );


    private:

        const char * _interface = "wlan0";

};

}; };
