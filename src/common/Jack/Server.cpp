/**
 * Jack client server
 *
 */
#include <iostream>
#include <jack/jack.h>

#include <Audio/Port.h>

#include "Server.h"

using Audio::Port;

namespace Jack {

/**
 * Construct
 *
 */

Server::Server() {

    _Audio = new Host();

    _Host = new LV2::Host( _client );

};


/**
 * Static sets
 */

const char * Server::UPDATE_EVENT = "update";


/**
 * Jack C server api start
 *
 */

bool Server::start() {

	// open a client connection to the JACK server

    _client = jack_client_open( _clientName, JACK_OPTIONS, &JACK_STATUS );

    if( _client == NULL ) {

        printf( "NOT CLIENT OPEN" );

        return false;

    }


    // tell the JACK server to call `process()'

    jack_set_process_callback( _client, Server::JackProcess, (void*)(this) );


    // tell the JACK server to call `jack_shutdown()' if it ever shuts down

    jack_on_shutdown( _client, Server::JackOnShutdown, 0 );

    JackRegisterPorts();

    jack_activate( _client );

    return true;

};


/**
 * Jack C server stop
 *
 */

bool Server::stop() {

    jack_deactivate( _client );

    jack_client_close( _client );

    return true;

};


/**
 * Jack C server connection
 *
 */

bool Server::connect() {

    return true;

};


/**
 * Jack register ports input output
 *
 */

void Server::JackRegisterPorts() {

    _Audio->setJackClient( _client );

    _Audio->createPorts();

};


/**
 * Get jack input and ports
 *
 */

void Server::getPorts() {

};


/**
 * Callback setting
 */

void Server::setClientCallbacks() {


};


/**
 * Jack server proccess callback
 *
 */

int Server::JackProcess( jack_nframes_t nframes, void * o ) {

    Server * s = (Server*) o;

    //std::cout << "NFRAMES420 " << nframes << "\n";

    s->dispatch( Server::UPDATE_EVENT, (void*) (uintptr_t) nframes );

    return 0;

};


/**
 * Jack server shutdown callback
 *
 */

void Server::JackOnShutdown( void *o ) {

    printf( "JACK HAS SHUTDOWN" );

};


/**
 * Connect default audio
 */

void Server::connectDefault() {

    vector<Port> ports = _Audio->getInputPorts();

    _Audio->connectOutputTo( ports[0].name, ports[1].name );

    _Audio->connectRedirect();

};

};
