/**
 * Jack client server
 *
 */
#include <iostream>
#include <jack/jack.h>

#include <Audio/Port.h>

#include "JackServer.h"


/**
 * Construct
 *
 */

JackServer::JackServer() {

    _Audio = new Audio::Jack();

};


/**
 * Jack C server api start
 *
 */

bool JackServer::start() {

	// open a client connection to the JACK server

    _client = jack_client_open( _clientName, JACK_OPTIONS, &JACK_STATUS );

    if( _client == NULL ) {

        printf( "NOT CLIENT OPEN" );

        return false;

    }


    // tell the JACK server to call `process()'

    jack_set_process_callback( _client, JackServer::JackProcess, 0 );


    // tell the JACK server to call `jack_shutdown()' if it ever shuts down

    jack_on_shutdown( _client, JackServer::JackOnShutdown, 0 );

    JackRegisterPorts();

    jack_activate( _client );

    return true;

};


/**
 * Jack C server stop
 *
 */

bool JackServer::stop() {

    jack_deactivate( _client );

    jack_client_close( _client );

};


/**
 * Jack C server connection
 *
 */

bool JackServer::connect() {

};


/**
 * Jack register ports input output
 *
 */

void JackServer::JackRegisterPorts() {

    _Audio->setJackClient( _client );

    _Audio->createPorts();

};


/**
 * Get jack input and ports
 *
 */

void JackServer::getPorts() {

    const char **ports;

    ports = jack_get_ports( _client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput );

    if( ports == NULL ) {
        fprintf(stderr, "no physical capture ports\n");
    }

    if( jack_connect( _client, ports[0], jack_port_name( _inputPort ) ) ) {

        fprintf(stderr, "cannot connect input ports\n");

    }

    free( ports );

    ports = jack_get_ports( _client, NULL, NULL, JackPortIsPhysical|JackPortIsInput );

    if( ports == NULL ) {

        fprintf(stderr, "no physical playback ports\n");

    }

    if( jack_connect( _client, jack_port_name( _outputPort ), ports[0] ) ) {

        fprintf(stderr, "cannot connect output ports\n");

    }

    free( ports );

};


/**
 * Jack server proccess callback
 *
 */

int JackServer::JackProcess( jack_nframes_t nframes, void *o ) {

    //std::cout << &o;

    return 0;

};


/**
 * Jack server shutdown callback
 *
 */

void JackServer::JackOnShutdown( void *o ) {

    printf( "JACK HAS SHUTDOWN" );

};


/**
 * Connect default audio
 */

void JackServer::connectDefault() {

    vector<Port> ports = _Audio->getPorts();

    _Audio->connectOutputTo( ports[0].name, ports[1].name );

    _Audio->connectRedirect();

};
