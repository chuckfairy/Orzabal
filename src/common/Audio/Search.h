/**
 * Search base
 *
 */
#pragma once

#include <vector>

#include "Plugin.h"
#include "PluginRepository.h"

using std::vector;


namespace Audio {


/**
 * Search base impl
 *
 */

class Search {

    public:

        /**
         * Get repo
         */

        PluginRepository<Plugin> * getRepo() {

            return & _Repo;

        };


        /**
         * Search All
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

                if( (*it)->hasMidi() && (*it)->hasAudio() ) {

                    midis.push_back( (*it) );

                }

            }

            return midis;

        };

        vector<Plugin*> findAudioEffects() {

            vector<Plugin*> plugins = findAll();

            vector<Plugin*> effects;

            vector<Plugin*>::iterator it;

            for( it = plugins.begin(); it != plugins.end(); ++ it ) {

                if( (*it)->hasInputs() && (*it)->hasOutputs() ) {

                    effects.push_back( (*it) );

                }

            }

            return effects;

        };

        Plugin * findById( const char * id ) {

            vector<Plugin*> plugins = findAll();

            vector<Plugin*>::iterator it;

            for( it = plugins.begin(); it != plugins.end(); ++ it ) {

                Plugin * p = (*it);

                if( strncmp( p->getID(), id, 500 ) == 0 ) {

                    return p;

                }

            }

        };


    protected:

        const char * _path;

        Search() {};
        ~Search() {};


    private:

        PluginRepository<Plugin> _Repo;

};

};
