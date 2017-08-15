/**
 * Search func
 */
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>
#include <Audio/PluginRepository.h>

#include "Search.h"
#include "Plugin.h"


namespace LV2  {


/**
 * Construct
 */

Search::Search( Host * h ) {

    _Host = h;

};


/**
 * Search via lilv world
 */

vector<Audio::Plugin*> Search::findAll() {

    if( getRepo()->empty() ) {

        update();

    }

    return getRepo()->getAll();

};


/**
 * Main update
 */

void Search::update() {

    getRepo()->clear();

    const LilvWorld * _lilvWorld = _Host->getLilvWorld();

    vector<Audio::Plugin*> pluginList;

    const LilvPlugins* plugins = lilv_world_get_all_plugins( _lilvWorld );

    LILV_FOREACH( plugins, i, plugins ) {

        const LilvPlugin* p = lilv_plugins_get( plugins, i );

        Audio::Plugin * d = new Plugin( p, _Host );

        pluginList.push_back( d );

        getRepo()->add( d );

    }

};

};
