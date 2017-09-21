/**
 * Host audio mod
 *
 */
#pragma once

#include <string.h>
#include <vector>

#include <jack/jack.h>

#include <Audio/Host.h>
#include <Audio/Plugin.h>
#include <Audio/Port.h>

#include "ServerStandalone.h"
#include "Port.h"


using std::string;
using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Jack {

/**
 * Forwarding
 */
class Server;


/**
 * Main class
 */

class Host :
    public Audio::Host, public ServerStandalone
{

    public:

        /**
         * Constructs
         *
         */

        explicit Host( jack_client_t * );

        explicit Host( Server * );


        /**
         * Default start
         *
         */

        void start();


        /**
         * Get specific ports
         */

        vector<Port> getPortsByType( enum JackPortFlags, const char * );


        /**
         * Get specific ports
         */

        vector<Port> getInputPorts();


        /**
         * Get specific ports
         */

        vector<Port> getOutputPorts();


        /**
         * Internal jack outputs get
         */

        vector<jack_port_t*> * getJackInputPorts() {

            return & _inputPorts;

        };

        vector<jack_port_t*> * getJackOutputPorts() {

            return & _outputPorts;

        };


        /**
         * Get port name
         */

        const char * getPortFullName( const char * name ) {

            char * c = (char*) malloc(180);

            sprintf( c, "orzabal:%s", name );

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

        int connectJackPort( const char * source, const char * destination );

        int disconnectJackPort( jack_port_t * );


        /**
         * Host Connection port methods
         *
         */

        bool connectInputTo( const char * );

        bool connectInputTo( const char *, const char * );

        bool connectOutputTo( const char * );

        bool connectOutputTo( const char *, const char * );


        /**
         * Disconnections
         */

        void disconnectInputs();

        void disconnectOutputs();


        /**
         * Redirect output to input
         */

        void redirectInput( jack_nframes_t );


        /**
         * Server set callbacks
         */

        void setServerCallbacks();

        /**
         * Jack updateing
         */

        void updateJack( jack_nframes_t );

        void updateJack( void * );

        void updateJackLatency( void * );

        void updateJackBufferSize( void * );


    protected:

        const char * _name = "orzabal-audio";


        /**
         * Host output ports
         */

        jack_port_t * _outputLeft;

        jack_port_t * _outputRight;

        const char * _outputLeftName = "output-L";

        const char * _outputRightName = "output-R";

        vector<jack_port_t*> _outputPorts;

        /**
         * Host input port
         */

        jack_port_t * _inputLeft;

        jack_port_t * _inputRight;

        const char * _inputLeftName = "input-L";

        const char * _inputRightName = "input-R";

        vector<jack_port_t*> _inputPorts;


        //@TODO possibly remove

        string * _lastOutputLeft;

        string  * _lastOutputRight;


        /**
         * From orzabal server
         */

        Server * _Server = NULL;

};

};
