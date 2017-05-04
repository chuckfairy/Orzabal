/**
 * Audio UI base
 *
 */
#pragma once

#include <vector>

#include "Plugin.h"

#include "UIDriver.h"


namespace Audio {


/**
 * Class header
 *
 */

class UI {

    protected:

        Plugin * _Plugin;

        vector<UIDriver*> _drivers;

        static vector<UIDriver*> DEFAULT_DRIVERS;


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

};

};
