/**
 * Repo manager of plugins impl
 */
#include <vector>

#include <lilv/lilv.h>

#include "Host.h"
#include "Plugin.h"
#include "Repository.h"

namespace LV2 {

/**
 * Constructs
 */

Repository();

Repository( Host * h ) : _Host( h ) {

};


/**
 * Main update of repo in case of change
 */

void Repository::update() {

    const LilvWorld * _lilvWorld = _Host->getLilvWorld();

    const LilvPlugins* plugins = lilv_world_get_all_plugins( _lilvWorld );

    LILV_FOREACH( plugins, i, plugins ) {

        const LilvPlugin * lilvPlugin = lilv_plugins_get(plugins, i);

        const char * uri = lilv_node_as_uri( lilv_plugin_get_uri( lilvPlugin ) );

        if( ! hasByURI( uri ) ) {

            Audio::Plugin * audioPlugin = new Plugin( p, _Host );

            add( audioPlugin );

        }

    }

};


/**
 * Extra repo finds
 */

bool Repository::hasByURI( const char * uri ) {

    vector<Plugin>::iterator it = getIterator();

    for( it; it != _items.end(); ++ it ) {

        plugin = (Plugin*)(*it);

        const char * uri = plugin->getURI();

    }

};

};
