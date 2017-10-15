/**
 * Patchbay effects list and jack port connection
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>
#include <Audio/ControlInterface.h>

#include "Host.h"
#include "Plugin.h"
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

class PatchbayEffects :
    public Audio::Patchbay,
    public StereoHostInterface,
    public Audio::ControlInterface
{

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
         * Get repo
         */

        PluginRepository * getRepo() {

            return _Repo;

        };


        /**
         * Get control ports of active plugins
         */

        vector<Audio::Port*> getControlPorts();


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
         * Main jack updates
         */

        void updateJack( jack_nframes_t );

        void updateJackBufferSize( jack_nframes_t );

        void updateJackLatency( jack_latency_callback_mode_t );


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

