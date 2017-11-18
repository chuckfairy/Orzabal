/**
 * Basic manager for wifi and other networks
 */
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdexcept>
#include <string>
#include <vector>

#include <iwlib.h>

#include "Manager.h"


using std::string;
using std::vector;


namespace Orza { namespace Network {


Manager::Manager() {

};


vector<Network*> Manager::getNetworks() {

    vector<Network*> out;

    wireless_scan_head head;
    wireless_scan *result;
    iwrange range;
    int sock;

    /* Open socket to kernel */
    sock = iw_sockets_open();

    /* Get some metadata to use for scanning */
    if (iw_get_range_info(sock, _interface, &range) < 0) {
        throw std::runtime_error(
            "Error during iw_get_range_info. Aborting."
        );
    }

    /* Perform the scan */
    if( iw_scan( sock, (char*) _interface, range.we_version_compiled, &head ) < 0 ) {
        throw std::runtime_error(
            "Error during iw_scan. Aborting."
        );
    }


    /* Traverse the results */

    result = head.result;

    while (NULL != result) {

        Network * net = new Network;

        net->ssid = result->b.essid;

        result = result->next;


        //Hide hidden

        if( net->ssid.empty() ) { continue; }

        //net->wep = result->b.key;

        out.push_back( net );

    }

    return out;

};


/**
 * Get networks ssids loop through getter
 */

vector<string> Manager::getNetworkSSIDs() {

    vector<string> out;

    vector<Network*> nets = getNetworks();

    if( nets.empty() ) { return out; }


    //Loop through push back SSIDs

    vector<Network*>::const_iterator it;

    for( it = nets.begin(); it != nets.end(); ++ it ) {

        out.push_back( (*it)->ssid );

    }

    return out;

};


/**
 * Main connect to new network
 */

void Manager::connect( string ssid, string pass ) {

    char * cmd = (char*) malloc(
        sizeof( ssid )
        + sizeof( pass )
        + 100
    );

    sprintf( cmd, "wpa_passphrase '%s' '%s' | sudo tee -a /etc/wpa_supplicant.conf", ssid.c_str(), pass.c_str() );

    std::cout << cmd << "\n";


    //Restart wpa_supplicant
    //@TODO specify interface

    system( cmd );
    system( "sudo wpa_supplicant -B -D wext -i wlan0 -c /etc/wpa_supplicant.conf" );

};

}; };
