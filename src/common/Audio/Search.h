/**
 * Search base
 *
 */
#pragma once

#include <vector>

#include "Plugin.h"

using std::vector;


namespace Audio {


/**
 * Search base impl
 *
 */

class Search {

    protected:

        const char * _path;


    public:

        Search() {};
        ~Search() {};

        /**
         * Search All
         *
         */

        virtual vector<Plugin*> findAll() {

            vector<Plugin*> pluginList;

            return pluginList;

        };

        vector<Plugin*> findMidiInstruments() {

            vector<Plugin*> plugins = findAll();

            vector<Plugin*> midis;

            vector<Plugin*>::iterator it;

            for( it = plugins.begin(); it != plugins.end(); ++ it ) {

                if( (*it)->hasMidi() ) {

                    midis.push_back( (*it) );

                }

            }

            return midis;

        };

};

};
