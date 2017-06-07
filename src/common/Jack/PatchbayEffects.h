/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>

#include "Host.h"
#include "ServerStandalone.h"


namespace Jack {


/**
 * Class forwards
 */

class Server;


/**
 * Construct
 */

class PatchbayEffects : public Audio::Patchbay, public ServerStandalone {

    public:

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

        void connectAudioEffectLastPort( Audio::Plugin * );


        /**
         * Main jack update
         */

        void updateJack( jack_nfames_t );


    protected:

};

};

