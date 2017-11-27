/**
 * Jack host impl
 *
 */
#include <vector>
#include <jack/jack.h>

#include <Util/Repository.h>
#include <Util/Vector.h>

#include "Server.h"
#include "Patchbay.h"
#include "Midi.h"
#include "Port.h"
#include "Plugin.h"
#include "PatchbayEffects.h"
#include "PluginRepository.h"

#include "Events/UpdateEvent.h"
#include "Events/LatencyEvent.h"
#include "Events/BufferEvent.h"


using std::vector;


namespace Jack {


/**
 * Construct
 */

Patchbay::Patchbay( Server * s ) :
    StereoHostInterface( s->getJackClient() ),
    _Server( s ),
    _PatchbayEffects( new PatchbayEffects( s ) )
{

    _Server->getAudio()->connectInputTo(
        _PatchbayEffects->getPatchbayOutput()->getOutputNameLeft(),
        _PatchbayEffects->getPatchbayOutput()->getOutputNameRight()
    );

    setServerCallbacks();


    //@TODO determine place
    run();

};


/**
 * Control overrides
 */

void Patchbay::run() {

    setActive( true );

};

void Patchbay::pause() {

    setActive( false );

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
 * Get control ports for current plugins
 */

vector<Audio::Port*> Patchbay::getControlPorts() {

    vector<Audio::Port*> ports;

    Util::Vector::append( &ports, getInstrumentControlPorts() );

    Util::Vector::append( &ports, _PatchbayEffects->getControlPorts() );

    return ports;

};


/**
 * char
 */

vector<Audio::PluginPortContainer*> Patchbay::getPluginPortContainers() {

    vector<Audio::Plugin*> plugins = getAllPlugins();
    vector<Audio::Plugin*>::iterator it;

    vector<Audio::PluginPortContainer*> output;

    for( it = plugins.begin(); it != plugins.end(); ++ it ) {

        Audio::Plugin * p = (Audio::Plugin*) (*it);

        vector<Audio::Port*> ports = p->getPortsFromIndex( p->getControlPorts() );
        vector<Audio::Port*>::iterator portsIt;

        for( portsIt = ports.begin(); portsIt != ports.end(); ++ portsIt ) {

            output.push_back(
                new Audio::PluginPortContainer( p, (*portsIt) )
            );

        }

    }

    return output;

};


/**
 * @TODO move to instrument type patchbay effects
 */

vector<Audio::Port*> Patchbay::getInstrumentControlPorts() {

    vector<Audio::Port*> ports;

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActivePlugins.begin(); it != _ActivePlugins.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        vector<Audio::Port*> pluginPorts = p->getPortsFromIndex( p->getControlPorts() );

        Util::Vector::append( &ports, pluginPorts );

    };

    return ports;

};


/**
 * Get all active plugins fro effects
 */

vector<Audio::Plugin*> Patchbay::getAllPlugins() {

    vector<Audio::Plugin*> output;

    Util::Vector::append( &output, _ActivePlugins );
    Util::Vector::append( &output, _PatchbayEffects->getRepo()->getAll<Audio::Plugin>() );

    return output;

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

    //@TODO maybe move

    _Server->getMidi()->update( nframes );


    //Check if even active

    if( ! isActive() ) { return; }


    //@TODO move to more like patchbay effects

    vector<Audio::Plugin*>::iterator it;

    for( it = _ActivePlugins.begin(); it != _ActivePlugins.end(); ++ it ) {

        Plugin * p = (Plugin*) (*it);

        if( p->isActive() ) {

            p->updateJack( nframes );

        }

    }

    _PatchbayEffects->redirectInput( nframes );

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

    _PatchbayEffects->updateJackBufferSize( frames );

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

    _PatchbayEffects->updateJackLatency( mode );

};

};
