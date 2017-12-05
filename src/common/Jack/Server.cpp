/**
 * Jack client server
 *
 */
#include <iostream>
#include <stdexcept>

#include <jack/jack.h>
#include <jack/midiport.h>
#include <jack/session.h>
#include <jack/metadata.h>

#include <Audio/Port.h>

#include "Midi.h"
#include "Server.h"
#include "PatchbayEffects.h"
#include "Events/PortRegistrationData.h"
#include "Resource/Client.h"


using Audio::Port;


namespace Jack {

using Events::PortRegistrationData;


/**
 * Construct
 *
 */

Server::Server() {

    _client = Resource::Client::getInstance();


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

    //jack_set_port_connect_callback(
        //_client,
        //Server::JackOnPortConnect,
        //(void*)(this)
    //);


    //Register host classes

    jack_activate( _client );


    //Host starting

    _Audio = new Host( this );
    _Audio->createPorts();
    _Audio->setServerCallbacks();

    _Midi = new Midi( this );

    _Host = new Jack::Patchbay( this );

};


/**
 * Static sets
 */

const char * Server::JACK_CLIENT_NAME = "orzabal-client";

const char * Server::UPDATE_EVENT = "update";
const char * Server::SHUTDOWN_EVENT = "shutdown";
const char * Server::LATENCY_EVENT = "latency";
const char * Server::BUFFER_SIZE_EVENT = "buffer-size";
const char * Server::PORT_REGISTER_EVENT = "port-register";


/**
 * Jack C server api start
 *
 */

void Server::start() {

	// open a client connection to the JACK server

    if( _client == NULL ) {

        throw std::runtime_error( "NO CLIENT OPEN" );

    }

    setActive( true );

};


/**
 * Main run func
 */
void Server::run() {

    //jack_activate( _client );

};


/**
 * Jack C server stop
 *
 */

void Server::stop() {

    jack_deactivate( _client );

    setActive( false );

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

};


/**
 * Get jack input and ports
 *
 */

void Server::getPorts() {

};

/**
 * Get midi
 */

Midi * Server::getMidi() {

    return _Midi;

};


/**
 * Get patchbay
 */

Jack::Patchbay * Server::getPatchbay() {

    return _Host;

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

};


/**
 * Port registered or unregistered impl
 * Uses dispatcher for reuse
 */

void Server::JackOnPortResgistration(
    jack_port_id_t id,
    int registry,
    void * serverPtr
) {

    Util::Dispatcher * s = (Util::Dispatcher*) serverPtr;

    PortRegistrationData * data = new PortRegistrationData( id, registry );

    //s->dispatch( Server::PORT_REGISTER_EVENT, (void*) data );

};

};
