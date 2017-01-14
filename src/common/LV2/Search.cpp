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

    const LilvWorld * _lilvWorld = _Host->getLilvWorld();

    vector<Audio::Plugin*> pluginList;

    const LilvPlugins* plugins = lilv_world_get_all_plugins( _lilvWorld );

    LILV_FOREACH( plugins, i, plugins ) {

        const LilvPlugin* p = lilv_plugins_get(plugins, i);

        Audio::Plugin * d = new Plugin( p, _Host );

        pluginList.push_back( d );

    }

    return pluginList;

};

};
