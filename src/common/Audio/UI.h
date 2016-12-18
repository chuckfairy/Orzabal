/**
 * Audio UI base
 *
 */
#pragma once

#include "Plugin.h"


namespace Audio {


/**
 * Class header
 *
 */

class UI {

    protected:

        Plugin * _Plugin;

    public:

        UI() {};
        ~UI() {};

        /**
         * Main plugin setter;
         *
         */

        void setPlugin( Plugin * p ) {

            _Plugin = p;

        };

};

};
