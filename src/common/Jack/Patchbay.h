/**
 * Patchbay highest level connection audio to effects and plugins
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>
#include <Audio/ControlInterface.h>
#include <Audio/PluginPortContainer.h>

#include "Host.h"
#include "StereoHostInterface.h"


namespace Jack {

/**
 * Class forwards
 */

class Server;

class PatchbayEffects;


/**
 * Construct
 */

class Patchbay :
    public Audio::Patchbay,
    public Audio::ControlInterface,
    public StereoHostInterface
{

    public:

        explicit Patchbay( Server * );


        /**
         * Control methods
         */

        void start() {};
        void stop() {};

        void run();
        void pause();


        /**
         * Add plugin as instrument
         * probably rename to addInstrument
         */

        void addPlugin( Audio::Plugin * );

        void removePlugin( uint32_t );

        void clearPlugins();


        /**
         * Audio effects related
         */

        void addAudioEffect( Audio::Plugin * );

        void removeAudioEffects( uint32_t );

        void clearAudioEffects();


        /**
         * host extensions
         *
         */

        unsigned int getSampleRate() {

            return jack_get_sample_rate( _jackClient );
        };

        int getBufferSize() {

            return jack_get_buffer_size( _jackClient );

        };

        int getMidiBufferSize() {

            return jack_port_type_get_buffer_size( _jackClient, JACK_DEFAULT_MIDI_TYPE );

        };


        /**
         * Get control ports for current plugins
         */

        vector<Audio::Port*> getControlPorts();

        vector<Audio::PluginPortContainer*> getPluginPortContainers();


        /**
         * @TODO move to instrument type patchbay effects
         */

        vector<Audio::Port*> getInstrumentControlPorts();


        /**
         * Get all active plugins fro effects
         */

        vector<Audio::Plugin*> getAllPlugins();


        /**
         * Connectors
         */

        void connectPluginPorts( Audio::Plugin * );

        void connectPluginAudioPorts( Audio::Plugin * );

        void connectPluginMidiPorts( Audio::Plugin * );


        /**
         * Update callback and hosting
         */

        void updateJack( jack_nframes_t );

        void updateJack( void * );

        void updateJackLatency( void * );

        void updateJackBufferSize( void * );


        /**
         * Server default callbacks
         */

        void setServerCallbacks();


        /**
         * Audio Effects
         */

        PatchbayEffects * getEffects();


    protected:

        Server * _Server;


        /**
         * Effect connectors
         */

        void connectAudioEffectLastPort( Audio::Plugin * );


    private:

        /**
         * Patchbay effects rack
         */

        PatchbayEffects * _PatchbayEffects;

};

};
