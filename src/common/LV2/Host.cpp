/**
 * LV2 Host extended from Jack
 *
 */
#include <stdexcept>
#include <vector>

#include <Jack/Host.h>
#include <Jack/Server.h>
#include <Audio/Plugin.h>

#include "Host.h"
#include "Search.h"
#include "JackCallbackEvent.h"
#include "Events/JackLatencyEvent.h"
#include "Events/JackBufferEvent.h"


using std::vector;

namespace LV2 {


/**
 * Construct
 */

Host::Host( Jack::Server * s ) : Jack::Patchbay( s->getJackClient() ) {

    _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

    setServer( s );

    _Search = new Search( this );

};


/**
 * Construct
 */

Host::Host( jack_client_t * c ) : Jack::Patchbay( c ) {

    _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

    _Search = new Search( this );

};


/**
 * Plugin starting
 */

void Host::addPlugin( Audio::Plugin * p ) {

    _ActivePlugins.push_back( p );

    p->start();
    ((LV2::Plugin*)p)->run();

};

void Host::addPluginByIndex( uint32_t i ) {

    //@TODO move to repository class
    //@TODO really is instruments

    vector<Audio::Plugin*> plugins = findAllInstruments();

    addPlugin( plugins[ i ] );

};


/**
 * Search methods
 */

vector<Audio::Plugin*> Host::findAllPlugins() {

    return _Search->findAll();

};

vector<Audio::Plugin*> Host::findAllInstruments() {

    return _Search->findMidiInstruments();

};


/**
 * Future repo update method
 */

void Host::updatePlugins() {

    if( _Plugins.empty() ) {

        _Plugins = _Search->findAll();

    }

};


/**
 * Callback event getter
 *
 */

JackCallbackEvent * Host::getEvent() {

    _Callback = new JackCallbackEvent( this );

    return _Callback;

};


/**
 * Static host setting and runtime
 * mainly testing related
 *
 */

void Host::setAsStaticHost() {

    jack_set_process_callback( _JackClient, Host::updateStaticHost, (void*)(this) );

};

int Host::updateStaticHost( jack_nframes_t nframes, void * hostPtr ) {

    Host * h = (Host*) hostPtr;

    h->updateJack( nframes );

    return 0;

};


/**
 * Server related
 *
 * @throws runtime_error if server incorrectly set
 *
 */

void Host::setServerCallbacks() {

    if( ! _Server ) {

        throw std::runtime_error( "No server set" );

    }

    Util::Event * e = (Util::Event*) getEvent();

    Util::Event * latency = (Util::Event*) new JackLatencyEvent( this );

    Util::Event * bufferEvent = (Util::Event*) new JackBufferEvent( this );

    _Server->on( Jack::Server::UPDATE_EVENT, e );

    _Server->on( Jack::Server::LATENCY_EVENT, latency );

    _Server->on( Jack::Server::BUFFER_SIZE_EVENT, bufferEvent );

};


/**
 * Update jack host from jack frame pointer
 */

void Host::updateJack( jack_nframes_t nframes ) {

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

void Host::updateJack( void * frameVoid ) {

    return updateJack(
        (jack_nframes_t) (uintptr_t) frameVoid
    );

};


/**
 * Update jack host from jack frame pointer
 */

void Host::updateJackBufferSize( void * bufferPtr ) {

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

void Host::updateJackLatency( void * modePtr ) {

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
