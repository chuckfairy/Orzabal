/**
 * LV2 Host extended from Jack
 *
 */
#pragma once

#include <vector>
#include <inttypes.h>

#include <lilv/lilv.h>

#include <Jack/Patchbay.h>
#include <Audio/Plugin.h>


using std::vector;


/**
 * Class fowarding
 */

namespace Jack {

class Server;

};


namespace LV2 {


/**
 * fowarding
 */

class JackCallbackEvent;

class Plugin;


/**
 * Construct
 */

class Host : public Jack::Patchbay {

    private:

        LilvWorld * _lilvWorld;

        JackCallbackEvent * _Callback;


    public:

        Host( Jack::Server * s );

        Host( jack_client_t * c );


        /**
         * Plugin Getters
         */

        vector<Audio::Plugin*> getPlugins() {

            return _Plugins;

        };

        /**
         * Plugin starting
         */

        void addPlugin( Audio::Plugin * p );

        void addPluginByIndex( uint32_t );

        void removePlugin( uint32_t );

        void clearPlugins();


        /**
         * Getter helpers
         */

        Audio::Plugin * getPluginByIndex( uint32_t i );


        /**
         * Lilv specific
         */

        LilvWorld * getLilvWorld() {

            return  _lilvWorld;

        };


        /**
         * Search methods
         */

        vector<Audio::Plugin*> findAllPlugins();

        vector<Audio::Plugin*> findAllInstruments();


        /**
         * Repo methods
         */

        void updatePlugins();


        /**
         * Update callback and hosting
         */

        JackCallbackEvent * getEvent();

        void updateJack( jack_nframes_t );

        void updateJack( void * );

        void updateJackLatency( void * );

        void updateJackBufferSize( void * );


        /**
         * Server related
         */

        void setServerCallbacks();

};

};
