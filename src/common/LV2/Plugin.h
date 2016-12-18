/**
 * LV2 Plugin
 *
 */
#pragma once

#include <iostream>
#include <string.h>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>


namespace LV2 {

class Plugin : public Audio::Plugin {

    private:

        const LilvPlugin *  _lilvPlugin;

        LilvWorld * _lilvWorld;

        Lil * _lilvInstance;

        char _lilvURI[500];


    protected:

        const char * TYPE = "LV2";


    public:

        Plugin( const LilvPlugin * p, LilvWorld * _lilvWorld );

        Audio::Port createPort( long portNum );


        /**
         * Virtual construction
         *
         */

        void setPorts();

        void start();


        /**
         * Lilv plugin related
         */

        const LilvPlugin * getLilvPlugin() {

            return _lilvPlugin;

        };

        void setLilvPlugin( const LilvPlugin* p );


        /**
         * lilv world related
         *
         */

        LilvWorld * getLilvWorld() {

            return _lilvWorld;

        };

        void setLilvWorld( LilvWorld * w ) {

            _lilvWorld = w;

        };

};

};
