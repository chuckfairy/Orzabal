/**
 * Plugin list static
 */
#include <iostream>
#include <vector>

#include <Audio/Plugin.h>

#include "PluginList.h"

#include <PluginSearch/LoadedPlugins.h>

namespace Orza { namespace CLI {

/**
 * List to std out
 */

void PluginList() {

    PluginSearch::LoadedPlugins::load();

    vector<Audio::Plugin*> plugins = PluginSearch::LoadedPlugins::getAll();

    vector<Audio::Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++ it ) {

        Audio::Plugin * p = (*it);

        char * c = (char*) malloc( 500 );

        sprintf( c, "%s : %s : %s\n", p->getType(), p->getName(), p->getID() );

        std::cout << c;

    }

};

}; };
