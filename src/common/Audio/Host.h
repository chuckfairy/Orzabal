/**
 * Audio host
 *
 */
#pragma once

#include "Search.h"


namespace Audio {


class Host {

    protected:

        Search * _Search;

    public:

        Host() {};
        ~Host() {};

        virtual unsigned int getSampleRate() {

            return 44100;

        };


        /**
         * Getters
         */

        Search * getSearch() {

            return _Search;

        };

};

};
