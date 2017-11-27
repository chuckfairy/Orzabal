/**
 * Stereo host interface base class
 */
#pragma once

#include <string.h>
#include <vector>

#include <jack/jack.h>

#include "ServerStandalone.h"

#include "Port.h"

using std::vector;
using std::string;

/**
 * char
 */

namespace Jack {


class StereoHostInterface : public ServerStandalone {

    public:

        /**
         * Get full name of port
         */

        const char * getPortFullName( const char * );


        /**
         * Internal jack outputs get
         */

        vector<jack_port_t*> * getInputPorts() {

            return & _inputPorts;

        };

        vector<jack_port_t*> * getOutputPorts() {

            return & _outputPorts;

        };

        jack_port_t * getInputPortLeft() {

            return _inputLeft;

        };

        jack_port_t * getInputPortRight() {

            return _inputRight;

        };

        jack_port_t * getOutputPortLeft() {

            return _outputLeft;

        };

        jack_port_t * getOutputPortRight() {

            return _outputRight;

        };

        const char * getInputNameLeft() {

            return jack_port_name( _inputLeft );

        };

        const char * getInputNameRight() {

            return jack_port_name( _inputRight );

        };

        const char * getOutputNameLeft() {

            return jack_port_name( _outputLeft );

        };

        const char * getOutputNameRight() {

            return jack_port_name( _outputRight );

        };


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
         * Redirection and helpers
         */

        void redirectInput( jack_nframes_t );

        static void redirectInputPort(
            jack_port_t * output,
            jack_port_t * input,
            jack_nframes_t nframes
        );


        /**
         * Connection clear methods
         */

        void clearInputs();

        void clearOutputs();


        /**
         * Port methods
         */

        vector<const char *> getConnectedPorts( Jack::Port * );


    protected:

        /**
         * Interface construction
         */

        StereoHostInterface( jack_client_t * );


        /**
         * Name prefix
         */

        virtual const char * getPrefix() { return ""; };


        /**
         * Host output ports
         */

        jack_port_t * _outputLeft;

        jack_port_t * _outputRight;

        const char * _outputLeftName = "output-L";

        const char * _outputRightName = "output-R";

        const char * _outputLeftNameFull;

        const char * _outputRightNameFull;

        vector<jack_port_t*> _outputPorts;

        /**
         * Host input port
         */

        jack_port_t * _inputLeft;

        jack_port_t * _inputRight;

        const char * _inputLeftName = "input-L";

        const char * _inputRightName = "input-R";

        const char * _inputLeftNameFull;

        const char * _inputRightNameFull;

        vector<jack_port_t*> _inputPorts;


        /**
         * Main port constructor
         */

        void createPorts();

};

};
