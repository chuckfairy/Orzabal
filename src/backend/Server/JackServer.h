/**
 * Jack server
 *
 */
#pragma once

#include "Server.h"

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <jack/jack.h>


/**
 * Jack server extension
 *
 */

class JackServer : public Server {

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




    protected:

        const char * _name = "gabrielo";
        const char * _clientName = "gabrielo-client";


    public:

        JackServer();

        bool start();

        bool stop();

        bool connect();

        void getPorts();


        /**
         * Get jack status
         *
         */

        jack_status_t * getJackStatus() {

            return &JACK_STATUS;

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
         * Jack process
         */

        static int JackProcess( jack_nframes_t nframes, void *o );

        static int JackOnSRateChange( jack_nframes_t n, void *o );

        static void JackOnShutdown( void *o );

};
