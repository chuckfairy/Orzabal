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

using Audio::Plugin;


namespace Orza { namespace PluginSearch {

vector<Audio::Plugin*> LoadedPlugins::ALL_PLUGINS;

vector<Audio::Search*> LoadedPlugins::PLUGIN_SEARCHS;

/**
 * API
 */

vector<Audio::Plugin*> LoadedPlugins::getAllGlobal() {

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

    ALL_PLUGINS.clear();

    vector<Audio::Search*>::iterator it;

    for( it = PLUGIN_SEARCHS.begin(); it != PLUGIN_SEARCHS.end(); ++it ) {

        vector<Audio::Plugin*> plugins = (*it)->findAll();

        Util::Vector::append<Audio::Plugin*>( &ALL_PLUGINS, plugins );

    }

};


/**
 * Getters
 */

vector<Audio::Plugin*> LoadedPlugins::getAll() {

    return getAllGlobal();

};

vector<Plugin*> LoadedPlugins::getMidiInstruments() {

    vector<Plugin*> plugins = getAll();

    vector<Plugin*> midis;

    vector<Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++ it ) {

        if( (*it)->hasMidi() && (*it)->hasAudio() ) {

            midis.push_back( (*it) );

        }

    }

    return midis;

};

vector<Plugin*> LoadedPlugins::getAudioEffects() {

    vector<Plugin*> plugins = getAll();

    vector<Plugin*> effects;

    vector<Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++ it ) {

        if( (*it)->hasInputs() && (*it)->hasOutputs() ) {

            effects.push_back( (*it) );

        }

    }

    return effects;

};

Plugin * LoadedPlugins::getById( const char * id ) {

    vector<Plugin*> plugins = getAll();

    vector<Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++ it ) {

        Plugin * p = (*it);

        if( strncmp( p->getID(), id, 500 ) == 0 ) {

            return p;

        }

    }

};

}; };
