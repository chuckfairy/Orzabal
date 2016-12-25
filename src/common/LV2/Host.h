/**
 * LV2 Host extended from Jack
 *
 */
#pragma once

#include <vector>

#include <lilv/lilv.h>

#include <Jack/Host.h>
#include <Audio/Plugin.h>


using std::vector;


namespace LV2 {


/**
 * Construct
 */

class Host : public Jack::Host {

    private:

        LilvWorld * _lilvWorld;

    public:

        Host( jack_client_t * c );


        /**
         * Lilv specific
         */

        LilvWorld * getLilvWorld() {

            return  _lilvWorld;

        };


        /**
         * Search methods
         */

        void setSearch();

        vector<Audio::Plugin*> findAllPlugins();

        vector<Audio::Plugin*> findAllInstruments();


};

};
