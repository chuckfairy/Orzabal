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

    public:

        explicit Host( Jack::Server * s );


        /**
         * Plugin Getters
         */

        vector<Audio::Plugin*> getPlugins() {

            return _Plugins;

        };


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


    private:

        LilvWorld * _lilvWorld;

        JackCallbackEvent * _Callback;

};

};
