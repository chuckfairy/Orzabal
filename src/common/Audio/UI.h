/**
 * Audio UI base
 *
 */
#pragma once

#include <vector>

#include "Plugin.h"


namespace Audio {

/**
 * Forwarding
 */

class UIDriver;


/**
 * Main Class
 */

class UI {

    protected:

        Plugin * _Plugin;

        vector<UIDriver*> _drivers;


    public:

        UI() {};
        ~UI() {};


        /**
         * Virtuals
         */

        virtual void start() {};

        virtual void stop() {};

        virtual void update() {};


        /**
         * Main plugin setter;
         *
         */

        void setPlugin( Plugin * p ) {

            _Plugin = p;

        };


        /**
         * Audio driver methods
         */

        void addDriver( UIDriver * );

        void addDrivers( vector<UIDriver*> );

        void startDrivers();

        void stopDrivers();

        void updateDrivers();

};

};
