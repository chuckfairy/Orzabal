/**
 * LV2 Host extended from Jack
 *
 */
#include <vector>

#include <Jack/Host.h>
#include <Audio/Plugin.h>

#include "Host.h"
#include "Search.h"


using std::vector;


namespace LV2 {

/**
 * Construct
 */

Host::Host( jack_client_t * c ) : Jack::Host( c ) {

    _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

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

    setSearch();

    return _Search->findAll();

}

};
