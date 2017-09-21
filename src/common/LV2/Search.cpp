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

#include <Jack/Resource/Client.h>

#include "Resource/World.h"
#include "Search.h"
#include "Plugin.h"


namespace LV2  {


/**
 * Construct
 */

Search::Search() {
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

    const LilvWorld * _lilvWorld = Resource::World::getResource();

    vector<Audio::Plugin*> pluginList;

    _lilvPlugins = lilv_world_get_all_plugins( _lilvWorld );

    LILV_FOREACH( plugins, i, _lilvPlugins ) {

        const LilvPlugin* p = lilv_plugins_get( _lilvPlugins, i );

        Plugin * d = new Plugin(
            p,
            Jack::Resource::Client::getInstance()
        );

        //_lv2s.push_back( *d );

        //pluginList.push_back( d );

        getRepo()->add( d );

    }

};

};
