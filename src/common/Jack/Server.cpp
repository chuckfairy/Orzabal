/**
 * Jack client server
 *
 */
#include <iostream>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <jack/session.h>
#include <jack/metadata.h>

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
const char * Server::SHUTDOWN_EVENT = "shutdown";
const char * Server::LATENCY_EVENT = "latency";
const char * Server::BUFFER_SIZE_EVENT = "buffer-size";


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

    jack_on_shutdown( _client, Server::JackOnShutdown, (void*)(this) );

	jack_set_buffer_size_callback( _client, Server::JackOnBufferSize, (void*)(this) );

	jack_set_latency_callback( _client, Server::JackOnLatency, (void*)(this) );

	//jack_set_session_callback( _client, &jack_buffer_size_cb, (void*)(this) );


    // tell the JACK server to call `jack_shutdown()' if it ever shuts down

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

    s->dispatch( Server::UPDATE_EVENT, (void*) (uintptr_t) nframes );

    return 0;

};


/**
 * Jack server shutdown callback
 *
 */

void Server::JackOnShutdown( void *o ) {

    Server * s = (Server*) o;

    s->dispatch( Server::SHUTDOWN_EVENT, nullptr );

    s->stop();

};


/**
 * Jack buffer size change
 *
 */

int Server::JackOnBufferSize( jack_nframes_t nframes, void *o ) {

    Server * s = (Server*) o;

    s->dispatch( Server::BUFFER_SIZE_EVENT, (void*) (uintptr_t) nframes );

    return 0;

};


/**
 * Jack server latency mode change
 *
 */

void Server::JackOnLatency( jack_latency_callback_mode_t mode, void *o ) {

    Server * s = (Server*) o;

    s->dispatch( Server::LATENCY_EVENT, (void*) mode );

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
