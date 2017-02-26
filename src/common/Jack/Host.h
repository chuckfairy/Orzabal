/**
 * Host audio mod
 *
 */
#pragma once

#include <vector>

#include <jack/jack.h>

#include <Audio/Host.h>
#include <Audio/Plugin.h>
#include <Audio/Port.h>


using Audio::Port;

using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Jack {


class Host : public Audio::Host {

    private:

        const char * _name = "gabrielo-audio";


        /**
         * Host output ports
         */

        jack_port_t * _outputLeft;

        jack_port_t * _outputRight;

        const char * _outputLeftName = "output-L";

        const char * _outputRightName = "output-R";


        /**
         * Host input port
         */

        jack_port_t * _inputLeft;

        jack_port_t * _inputRight;

        const char * _inputLeftName = "input-L";

        const char * _inputRightName = "input-R";


        static const char ** _portNames;


        /**
         * Host client pointer
         */

        jack_client_t * _jackClient;


    public:

        /**
         * Constructs
         *
         */

        Host();

        explicit Host( jack_client_t * j );


        /**
         * Default start
         *
         */

        void start();


        /**
         * main jack client from server
         */

        void setJackClient( jack_client_t * j ) {

            _jackClient = j;

        };

        jack_client_t * getJackClient() {

            return _jackClient;

        };


        /**
         * Get specific ports
         */

        vector<Port> getPortsByType( enum JackPortFlags );


        /**
         * Get specific ports
         */

        vector<Port> getInputPorts();


        /**
         * Get specific ports
         */

        vector<Port> getOutputPorts();


        /**
         * Get port name
         */

        const char * getPortFullName( const char * name ) {

            char * c = (char*) malloc(180);

            sprintf( c, "gabrielo-client:%s", name );

            return c;

        };


        /**
         * Internal port checker
         */

        bool isInternalPort( const char * );


        /**
         * Default ports
         *
         */

        void createPorts();


        /**
         * Abstract jack port connection method
         *
         */

        int connectJackPort( const char *, const char * );


        /**
         * Host Connection port methods
         *
         */

        bool connectInputTo( const char * );

        bool connectInputTo( const char *, const char * );

        bool connectOutputTo( const char * );

        bool connectOutputTo( const char *, const char * );

};

};
