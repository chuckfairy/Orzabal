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

#include <LV2/Host.h>


namespace Jack {


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

        jack_client_t * _client;


        /**
         * Audio module
         *
         */

        Host * _Audio;


        /**
         * LV2
         */

        LV2::Host * _Host;


    protected:

        const char * _name = "gabrielo";
        const char * _clientName = "gabrielo-client";


    public:

        Server();

        bool start();

        void run();

        bool stop();

        bool connect();

        void getPorts();

        void connectDefault();


        /**
         * Event specific
         */

        static const char * UPDATE_EVENT;
        static const char * SHUTDOWN_EVENT;
        static const char * LATENCY_EVENT;
        static const char * BUFFER_SIZE_EVENT;


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

        Host * getAudio() {

            return _Audio;

        };



        /**
         * Get status type
         *
         */
        const char * getJackStatusType() {

            if( JACK_STATUS & JackServerFailed ) {

                return "SERVER_FAILED";

            } else if( JACK_STATUS & JackServerStarted ) {

                return "SERVER_STARTED";

            } else if ( JACK_STATUS & JackNameNotUnique ) {

                return "SERVER_NAME_NOT_UNIQUE";

            }

            return "";

        };


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

};

};
