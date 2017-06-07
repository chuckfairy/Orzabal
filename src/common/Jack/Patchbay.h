/**
 * Patchbay highest level connection audio to effects and plugins
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

class Patchbay : public Audio::Patchbay, public ServerStandalone {

    public:

        explicit Patchbay( jack_client_t * );


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
         * Server related
         */

        void setServer( Server * );


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
         * Connectors
         */

        void connectPluginPorts( Audio::Plugin * );

        void connectPluginAudioPorts( Audio::Plugin * );

        void connectPluginMidiPorts( Audio::Plugin * );


        /**
         * Effect connectors
         */

        void connectAudioEffectPorts( Audio::Plugin * );


    protected:

        Server * _Server;


        /**
         * Effect connectors
         */

        void connectAudioEffectLastPort( Audio::Plugin * );

};

};
