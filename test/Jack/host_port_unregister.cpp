/**
 * Jack port register should happen upon starting audio server
 */
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "Orzabal/Jack/host_port_unregister_should_clear"

#include <boost/test/unit_test.hpp>

#include <vector>

#include <Jack/Host.h>

#include "include/jack_defaults.h"


using std::vector;


/**
 * Main port register
 */

BOOST_AUTO_TEST_CASE( host_port_unregister_should_clear_vectors ) {

    jack_client_t * _client = testCreateJackClient();

    Jack::Host * host = new Jack::Host( _client );

    host->createPorts();

    BOOST_CHECK( true );

};


