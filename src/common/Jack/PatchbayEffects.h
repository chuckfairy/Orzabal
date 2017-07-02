/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>

#include "Host.h"
#include "StereoHostInterface.h"


namespace Jack {


/**
 * Class forwards
 */

class Server;


/**
 * Construct
 */

class PatchbayEffects : public Audio::Patchbay, public StereoHostInterface {

    public:

        explicit PatchbayEffects( Server * );

        explicit PatchbayEffects( jack_client_t * );


        /**
         * Audio effects related
         */

        void addEffect( Audio::Plugin * );

        void removeEffects( uint32_t );

        void clearEffects();


        /**
         * Effect connectors
         */

        void connectEffectPorts( Audio::Plugin * );


        /**
         * Connect via last port in chain
         */

        void connectEffectLastPort( Audio::Plugin * );


        /**
         * Main jack update
         */

        void updateJack( jack_nframes_t );


        /**
         * Server set callbacks
         */

        void setServerCallbacks();


    protected:

        /**
         * Prefix virtual
         */

        const char * getPrefix() {

            return "effects";

        };


    private:

        Server * _Server;


};

};

