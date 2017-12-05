/**
 * Jack server
 *
 */
#pragma once

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <jack/jack.h>

#include <Audio/Server.h>
#include "Host.h"
#include "Patchbay.h"


namespace Jack {

/**
 * Forwarding
 */

class Midi;


/**
 * Jack server extension
 *
 */

class Server : public Audio::Server {

    private:

        jack_options_t JACK_OPTIONS = JackNullOption;

        jack_status_t JACK_STATUS;


        /**
         * Jack input port
         */

        jack_port_t * _inputPort;


        /**
         * Jack input port
         */

        jack_port_t * _outputPort;


        /**
         * Jack client pointer
         */

        jack_client_t * _client = 0;


        /**
         * Audio module
         *
         */

        Host * _Audio;


        /**
         * Midi connectors
         */

        Midi * _Midi;


        /**
         * LV2
         * @TODO rename to more patchbay
         */

        Jack::Patchbay * _Host;


    protected:

        const char * _name = "orzabal";
        const char * _clientName = "orzabal-client";


    public:

        Server();

        void start();

        void run();

        void stop();

        bool connect();

        void getPorts();

        void connectDefault();


        /**
         * Event specific
         */

        static const char * JACK_CLIENT_NAME;

        static const char * UPDATE_EVENT;
        static const char * SHUTDOWN_EVENT;
        static const char * LATENCY_EVENT;
        static const char * BUFFER_SIZE_EVENT;
        static const char * PORT_REGISTER_EVENT;


        /**
         * Get jack status
         *
         */

        jack_status_t * getJackStatus() {

            return &JACK_STATUS;

        };


        /**
         * Get jack client pointer
         *
         */

        jack_client_t * getJackClient() {

            return _client;

        };


        /**
         * Get Audio host
         *
         */

        Jack::Host * getAudio() {

            return _Audio;

        };

        /**
         * Getter audio modules
         */

        Midi * getMidi();

        Jack::Patchbay * getPatchbay();


        /**
         * Port regsiter of started server
         */

        void JackRegisterPorts();


        /**
         * Jack process functionsc
         *
         */

        static int JackProcess( jack_nframes_t, void * );

        static int JackOnBufferSize( jack_nframes_t, void * );

        static void JackOnLatency( jack_latency_callback_mode_t, void * );

        static void JackOnShutdown( void *o );

        static void JackOnPortConnect( void *o );


        /**
         * Port registered or unregistered
         *
         * see JackPortRegistrationCallback
         *
         */

        static void JackOnPortResgistration( jack_port_id_t, int, void * );

};

};
