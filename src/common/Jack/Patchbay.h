/**
 * Jack host base
 *
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Patchbay.h>

#include "Host.h"


namespace Jack {

/**
 * Class forwards
 */

class Server;


/**
 * Construct
 */

class Patchbay : public Audio::Patchbay {

    protected:

        jack_client_t * _JackClient;

        Server * _Server;


    public:

        explicit Patchbay( jack_client_t * );


        /**
         * Server related
         */

        void setServer( Server * );


        /**
         * host extensions
         *
         */

        unsigned int getSampleRate() {

            return jack_get_sample_rate( _JackClient );
        };

        int getBufferSize() {

            return jack_get_buffer_size( _JackClient );

        };

        int getMidiBufferSize() {

            return jack_port_type_get_buffer_size( _JackClient, JACK_DEFAULT_MIDI_TYPE );

        };


        /**
         * Jack client related
         *
         */

        void setJackClient( jack_client_t * c ) {

            _JackClient = c;

        };

        jack_client_t * getJackClient() {

            return _JackClient;

        };


        /**
         * Connectors
         */

        void connectPluginPorts( Audio::Plugin * );

        void connectPluginAudioPorts( Audio::Plugin * );

        void connectPluginMidiPorts( Audio::Plugin * );

};

};
