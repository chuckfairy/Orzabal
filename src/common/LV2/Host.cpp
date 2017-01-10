/**
 * LV2 Host extended from Jack
 *
 */
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

};


/**
 * Construct
 */

Host::Host( jack_client_t * c ) : Jack::Patchbay( c ) {

    _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

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

void Host::setSearch() {

    if( ! _Search ) {

        _Search = new Search( this );

    }

};

vector<Audio::Plugin*> Host::findAllPlugins() {

    updatePlugins();

    return _Plugins;

};

vector<Audio::Plugin*> Host::findAllInstruments() {

    setSearch();

    return _Search->findMidiInstruments();

};


/**
 * Future repo update method
 */

void Host::updatePlugins() {

    setSearch();

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

void Host::setStaticHost() {

};


/**
 * Update jack host from jack frame pointer
 */

void Host::updateJack( void * frameVoid ) {

    updatePlugins();

    vector<Audio::Plugin*>::iterator it;

    for( it = _Plugins.begin(); it != _Plugins.end(); ++ it ) {

        if( !(*it)->isActive() ) {

            return;

        }



    }

};

};
