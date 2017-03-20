/**
 * Server standalone trait setting
 *
 */
#pragma once

#include <jack/jack.h>

#include <Util/Dispatcher.h>


namespace Jack {

/**
 * Main server setting
 * Mainly for testing and external use
 *
 */

void ServerStandalone::setAsStandalone() {

    // Set jack callbacks

    jack_set_process_callback( _client, Server::JackProcess, (void*)(this) );

    jack_on_shutdown( _client, Server::JackOnShutdown, (void*)(this) );

	jack_set_buffer_size_callback( _client, Server::JackOnBufferSize, (void*)(this) );

	jack_set_latency_callback( _client, Server::JackOnLatency, (void*)(this) );

    jack_set_port_registration_callback(
        _client,
        Server::JackOnPortResgistration,
        (void*)(this)
    );

    jack_activate( _client );

};

};
