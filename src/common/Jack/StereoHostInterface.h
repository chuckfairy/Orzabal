/**
 * Stereo host interface base class
 */
#pragma once

#include <string.h>
#include <vector>

#include <jack/jack.h>

#include "ServerStandalone.h"

using std::vector;

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


    protected:

        /**
         * Interface construction
         */

        StereoHostInterface( jack_client_t * );


        /**
         * Name prefix
         */

        const char * PREFIX;


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

        void redirectInput( jack_nframes_t );


    private:

        /**
         * Main port constructor
         */

        void createPorts();

};

};
