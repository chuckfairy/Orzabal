/**
 * Loaded plugins search grab
 */
#pragma once

#include <Audio/Plugin.h>
#include <Audio/Search.h>

using std::vector;

using Audio::Plugin;

namespace Orza { namespace PluginSearch {

/**
 * Main class
 */

class LoadedPlugins {

    public:

        LoadedPlugins() {};

        /**
         * API
         */

        static void load();

        static void update();

        static vector<Audio::Plugin*> getAllGlobal();

        static void addSearch( Audio::Search * );


        /**
         * Class methods
         */

        vector<Audio::Plugin*> getAll();

        vector<Plugin*> getMidiInstruments();

        vector<Plugin*> getAudioEffects();

        Plugin * getById( const char * id );


        /**
         * Search getters
         */
        static vector<Audio::Search*> getAllSearches();


    private:

        void addVector( vector<Audio::Plugin*> source, vector<Audio::Plugin*> dest );

        static vector<Audio::Plugin*> ALL_PLUGINS;

        static vector<Audio::Search*> PLUGIN_SEARCHS;

};

}; };
