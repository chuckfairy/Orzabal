/**
 * Loaded plugins search grab
 */
#include <vector>

#include <common/Config/PluginTypes.h>
#include <Util/Vector.h>

#include "LoadedPlugins.h"

#if ORZABAL_HAS_LV2

#include <LV2/Search.h>

#endif

using std::vector;


namespace Orza { namespace PluginSearch {

vector<Audio::Plugin*> LoadedPlugins::ALL_PLUGINS;

vector<Audio::Search*> LoadedPlugins::PLUGIN_SEARCHS;

/**
 * API
 */

vector<Audio::Plugin*> LoadedPlugins::getAll() {

    return LoadedPlugins::ALL_PLUGINS;

};

void LoadedPlugins::addSearch( Audio::Search * s ) {

    LoadedPlugins::PLUGIN_SEARCHS.push_back( s );

};


/**
 * Main loader
 */

void LoadedPlugins::load() {

#if ORZABAL_HAS_LV2

    LV2::Search * LV2_PLUGIN = new LV2::Search();

    LoadedPlugins::addSearch( (Audio::Search*) LV2_PLUGIN );

#endif

    LoadedPlugins::update();

};


/**
 * Main updaet
 */

void LoadedPlugins::update() {

    //Loop searches and append to main vector

    vector<Audio::Search*>::iterator it;

    for( it = PLUGIN_SEARCHS.begin(); it != PLUGIN_SEARCHS.end(); ++it ) {

        vector<Audio::Plugin*> plugins = (*it)->findAll();

        Util::Vector::append<Audio::Plugin*>( &ALL_PLUGINS, plugins );

    }

};

}; };
