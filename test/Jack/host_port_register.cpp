/**
 * Jack port register should happen upon starting audio server
 */
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "Orzabal/Jack/host_port_register"

#include <boost/test/unit_test.hpp>

#include <vector>

#include <Jack/Host.h>

#include "include/jack_defaults.h"


using std::vector;


/**
 * Main port register
 */

BOOST_AUTO_TEST_CASE( host_port_register ) {

    jack_client_t * _client = testCreateJackClient();

    BOOST_CHECK( _client != NULL );

    Jack::Host * host = new Jack::Host( _client );

    host->createPorts();

    vector<jack_port_t*> * ports = host->getJackOutputPorts();

    BOOST_CHECK( ! ports->empty() );

    bool yes = jack_port_is_mine(
        _client, ports->at(0)
    );

    BOOST_CHECK( yes );

};
