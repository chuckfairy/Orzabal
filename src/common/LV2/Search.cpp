/**
 * Search func
 */
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>

#include "Search.h"


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

    vector<Audio::Plugin*> pluginList;

    LilvWorld * world = lilv_world_new();
    lilv_world_load_all(world);

    const LilvPlugins* plugins = lilv_world_get_all_plugins(world);

    LILV_FOREACH(plugins, i, plugins) {

        const LilvPlugin* p = lilv_plugins_get(plugins, i);

        //Plugin * _p = new Plugin( p );
        Audio::Plugin * d = new Plugin( p, world );

        pluginList.push_back( d );

    }

    //lilv_world_free(world);

    return pluginList;

};

};
