/**
 * Loaded plugins search grab
 */
#pragma once

#include <Audio/Plugin.h>
#include <Audio/Search.h>

using std::vector;

namespace Orza { namespace PluginSearch {

/**
 * Main class
 */

class LoadedPlugins {

    public:

        /**
         * API
         */

        static void load();

        static void update();

        static vector<Audio::Plugin*> getAll();

        static void addSearch( Audio::Search * );

    private:

        void addVector( vector<Audio::Plugin*> source, vector<Audio::Plugin*> dest );

        static vector<Audio::Plugin*> ALL_PLUGINS;

        static vector<Audio::Search*> PLUGIN_SEARCHS;

};

}; };
