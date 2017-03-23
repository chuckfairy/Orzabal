/**
 * Server standalone trait setting
 *
 */
#include <jack/jack.h>

#include <Util/Dispatcher.h>

#include "Server.h"


namespace Jack {

/**
 * Main server setting
 * Mainly for testing and external use
 *
 */

void ServerStandalone::setAsStandalone() {

    // Set jack callbacks

    jack_set_process_callback( _jackClient, Server::JackProcess, (void*)(this) );

    jack_on_shutdown( _jackClient, Server::JackOnShutdown, (void*)(this) );

	jack_set_buffer_size_callback( _jackClient, Server::JackOnBufferSize, (void*)(this) );

	jack_set_latency_callback( _jackClient, Server::JackOnLatency, (void*)(this) );

    jack_set_port_registration_callback(
        _jackClient,
        Server::JackOnPortResgistration,
        (void*)(this)
    );

    jack_activate( _jackClient );

};

};
