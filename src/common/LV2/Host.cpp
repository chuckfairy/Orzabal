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


using std::vector;

namespace LV2 {


/**
 * Construct
 */

Host::Host( Jack::Server * s ) : Jack::Patchbay( s->getJackClient() ) {

    _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

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

    p->start();
    _ActivePlugins.push_back( (Audio::Plugin*) p );

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

    if( ! _Callback ) {

        _Callback = new JackCallbackEvent( this );

    }

    return _Callback;

};


/**
 * Static host setting and runtime
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

        throw std::runtime_error("No server set");

    }

    Util::Event * e = (Util::Event*) getEvent();

    _Server->on( Jack::Server::UPDATE_EVENT, e );

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

};
