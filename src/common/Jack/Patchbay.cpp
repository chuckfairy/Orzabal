/**
 * Jack host impl
 *
 */
#include <jack/jack.h>

#include "Server.h"
#include "Patchbay.h"
#include "Midi.h"
#include "Port.h"
#include "Plugin.h"
#include "PatchbayEffects.h"

#include "Events/UpdateEvent.h"
#include "Events/LatencyEvent.h"
#include "Events/BufferEvent.h"


namespace Jack {


/**
 * Construct
 */

Patchbay::Patchbay( Server * s ) :
    ServerStandalone( s->getJackClient() ),
    _Server( s ),
    _PatchbayEffects( new PatchbayEffects( s ) )
{

    _Server->getAudio()->connectInputTo(
        _PatchbayEffects->getPatchbayOutput()->getOutputNameLeft(),
        _PatchbayEffects->getPatchbayOutput()->getOutputNameRight()
    );

};


/**
 * Plugin starting
 */

void Patchbay::addPlugin( Audio::Plugin * p ) {

    _ActivePlugins.push_back( p );

    p->start();

    connectPluginPorts( p );

    p->run();

};


/**
 * Remove active plugin
 */

void Patchbay::removePlugin( uint32_t index ) {

    if( ! _ActivePlugins[ index ] ) { return; }

    Audio::Plugin * p = _ActivePlugins[ index ];

    _ActivePlugins.erase( _ActivePlugins.begin() + index );

    p->stop();

};


/**
 * Clear all plugins
 */

void Patchbay::clearPlugins() {

    if( _ActivePlugins.empty() ) { return; }

    while( ! _ActivePlugins.empty() ) {

        removePlugin( 0 );

    }

}


/**
 * Effects list
 */

PatchbayEffects * Patchbay::getEffects() {

    return _PatchbayEffects;

};


/**
 * Plugin port connector to server audio
 */

void Patchbay::connectPluginPorts( Audio::Plugin * p ) {

    connectPluginAudioPorts( p );
    connectPluginMidiPorts( p );

};


/**
 * Audio outputs connector
 * @TODO support more than stereo
 *
 */

void Patchbay::connectPluginAudioPorts( Audio::Plugin * p ) {

    //Get outputs

    vector<long> * ports = p->getOutputPorts();

    if( ports->empty() ) { return; }


    //Stereo check

    if( ports->size() > 1 ) {

        Jack::Port * portLeft = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        Jack::Port * portRight = (Jack::Port*) p->getPort(
            (*ports)[ 1 ]
        );

        _PatchbayEffects->connectInputTo(
            jack_port_name( portLeft->jack_port ),
            jack_port_name( portRight->jack_port )
        );

    } else {

        Jack::Port * portMono = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        _PatchbayEffects->connectInputTo(
            jack_port_name( portMono->jack_port )
        );

    }

};


/**
 * Midi connector for plugin
 */

void Patchbay::connectPluginMidiPorts( Audio::Plugin * p ) {

    vector<long> * ports = p->getMidiPorts();

    if( ports->empty() ) { return; }


    //Connect to all midi inputs

    Jack::Midi * midi = _Server->getMidi();

    vector<long>::iterator it;

    for( it = ports->begin(); it != ports->end(); ++ it ) {

        Port * port = (Port*) p->getPort( *it );

        if( ! port->jack_port ) { continue; }

        if( port->flow == Audio::FLOW_INPUT ) {

            midi->addInput( port->jack_port );

        }

    }

};


/**
 * Audio effects connection
 */

void Patchbay::connectAudioEffectPorts( Audio::Plugin * plugin ) {


};

/*
 * Server related
 *
 * @throws runtime_error if server incorrectly set
 *
 */

void Patchbay::setServerCallbacks() {

    if( ! _Server ) {

        throw std::runtime_error( "No server set" );

    }

    Util::Event * e = new UpdateEvent( this );

    Util::Event * latency = new LatencyEvent( this );

    Util::Event * bufferEvent = new BufferEvent( this );

    _Server->on( Jack::Server::UPDATE_EVENT, e );

    _Server->on( Jack::Server::LATENCY_EVENT, latency );

    _Server->on( Jack::Server::BUFFER_SIZE_EVENT, bufferEvent );

};


/**
 * Update jack host from jack frame pointer
 */

void Patchbay::updateJack( jack_nframes_t nframes ) {

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActivePlugins.begin(); it != _ActivePlugins.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( p->isActive() ) {

            p->updateJack( nframes );

        }

    }

};


/**
 * Update jack from possible void *
 */

void Patchbay::updateJack( void * frameVoid ) {

    return updateJack(
        (jack_nframes_t) (uintptr_t) frameVoid
    );

};


/**
 * Update jack host from jack frame pointer
 */

void Patchbay::updateJackBufferSize( void * bufferPtr ) {

    std::cout << "BUFFER SIZE\n";

    jack_nframes_t frames = (jack_nframes_t) (uintptr_t) bufferPtr;

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActivePlugins.begin(); it != _ActivePlugins.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( p->isActive() ) {

            p->updateJackBufferSize( frames );

        }

    }

};


/**
 * Update jack latency host for plugin jack ports
 */

void Patchbay::updateJackLatency( void * modePtr ) {

    jack_latency_callback_mode_t mode = (jack_latency_callback_mode_t) (uintptr_t) modePtr;

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActivePlugins.begin(); it != _ActivePlugins.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( p->isActive() ) {

            p->updateJackLatency( mode );

        }

    }

};

};
