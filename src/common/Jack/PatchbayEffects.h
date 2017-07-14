/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>

#include "Host.h"
#include "StereoHostInterface.h"
#include "PatchbayEffectsOutput.h"


namespace Jack {


/**
 * Class forwards
 */

class Server;
class PluginRepository;


/**
 * Main class
 */

class PatchbayEffects : public Audio::Patchbay, public StereoHostInterface {

    public:

        explicit PatchbayEffects( Server * );

        explicit PatchbayEffects( jack_client_t * );


        /**
         * Getters
         */

        PatchbayEffectsOutput * getPatchbayOutput() {

            return _Output;

        };


        /**
         * Audio effects related
         */

        void addEffect( Audio::Plugin * );

        void removeEffect( Audio::Plugin * );

        void pauseEffect( Audio::Plugin * );

        void clearEffects();


        /**
         * Effect connectors
         */

        void connectEffectPorts();


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


        /**
         * Redirect overwrite over hostinterface
         */

        void redirectInput( jack_nframes_t );


    protected:

        /**
         * Prefix virtual
         */

        const char * getPrefix() {

            return "effects";

        };


    private:

        Server * _Server;

        PatchbayEffectsOutput * _Output;

        void redirectEffects( jack_nframes_t );

        void disconnectEffectPorts();

        PluginRepository * _Repo;



};

};

