/**
 * Plugin abstract
 *
 */
#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <inttypes.h>

#include "Port.h"

using std::vector;
using std::map;
using std::string;


namespace Audio {


/**
 * Class forwarding
 */
class UI;


/**
 * Base plugin class
 *
 */

class Plugin {

    protected:

        bool ACTIVE = false;

        char TYPE[10];

        uint32_t _portsNum;

        map<long, Port*> _ports;

        vector<long> _audioPorts;

        vector<long> _inputs;

        vector<long> _outputs;

        vector<long> _midiPorts;

        vector<long> _controlPorts;

        char name[255];

        int long _numPorts;

        UI * _UI;


    public:

        Plugin() {};

        ~Plugin() {};


        /**
         * Get type
         *
         */

        const char * getType() {

            return TYPE;

        };


        /**
         * Get name of plugin
         * name related
         *
         */

        char * getName() {

            return name;

        };

        void setName( const char * s ) {

            strcpy( name, s );

        };


        /**
         * Is on / connected
         *
         */

        bool isActive() {

            return ACTIVE;

        };


        /**
         * UI related
         */

        UI * getUI();


        /**
         * Map and set port
         * Will include port types midi and others
         *
         */

        void setPort( long index, Port * port ) {

            _ports[ index ] = port;

            switch( port->type ) {

                case TYPE_CONTROL:
                    _controlPorts.push_back( index );
                    break;

                case TYPE_AUDIO:
                    _audioPorts.push_back( index );
                    port->flow == FLOW_INPUT
                        ? _inputs.push_back( index )
                        : _outputs.push_back( index );
                    break;

                case TYPE_EVENT:
                    _midiPorts.push_back( index );
                    break;

                default: case TYPE_UNKNOWN: case TYPE_CV:
                    break;

            }

        };


        /**
         * Has port type methods
         */

        bool hasMidi() { return ! _midiPorts.empty(); };

        bool hasAudio() { return ! _audioPorts.empty(); };

        bool hasInputs() { return ! _inputs.empty(); };

        bool hasOutputs() { return ! _outputs.empty(); };


        /**
         *  Port getter
         */

        Port * getPort( long index ) {

            return _ports[ index ];

        };

        vector<long> * getMidiPorts() {

            return &_midiPorts;

        };

        vector<long> * getAudioPorts() {

            return &_audioPorts;

        };

        vector<long> * getInputPorts() {

            return &_inputs;

        };

        vector<long> * getOutputPorts() {

            return &_outputs;

        };


        /**
         * Create a port
         *
         */

        virtual Port * createPort( long portNum ) {

            Port * p = new Port;

            return p;

        };


        /**
         * Start up for lv2
         */

        virtual void start() {};

};

};
