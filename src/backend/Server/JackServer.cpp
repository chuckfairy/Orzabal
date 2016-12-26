/**
 * Jack client server
 *
 */
#include <iostream>
#include <jack/jack.h>

#include <Audio/Port.h>

#include "JackServer.h"

using Audio::Port;


/**
 * Construct
 *
 */

JackServer::JackServer() {

    _Audio = new Audio::Jack();

    _Host = new LV2::Host( _client );

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

    jack_set_process_callback( _client, JackServer::JackProcess, (void*)(this) );


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

    return true;

};


/**
 * Jack C server connection
 *
 */

bool JackServer::connect() {

    return true;

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

    vector<Port> ports = _Audio->getInputPorts();

    _Audio->connectOutputTo( ports[0].name, ports[1].name );

    _Audio->connectRedirect();

};
