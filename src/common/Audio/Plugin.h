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

    public:

        Plugin() {};

        ~Plugin() {};


        /**
         * Get type
         */

        virtual const char * getType() {

            return "";

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
         * Id related
         */

        char * getID() {

            return (char*) &id;

        };

        void setID( const char * s ) {

            strcpy( id, s );

        };


        /**
         * Is on / connected
         *
         */

        bool isActive() {

            return ACTIVE;

        };


        /**
         * Port getters count
         */

        int getNumPorts() {

            return _numPorts;

        };


        /**
         * UI related
         */

        virtual UI * getUI() {

            return nullptr;

        };


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
                    break;

                case TYPE_EVENT:
                    _midiPorts.push_back( index );
                    break;

                default: case TYPE_UNKNOWN: case TYPE_CV:
                    break;

            }


            //Set audios

            if( port->type == TYPE_AUDIO ) {

                port->flow == FLOW_INPUT
                    ? _inputs.push_back( index )
                    : _outputs.push_back( index );

            }

        };


        /**
         * Set port value virtual
         */

        virtual void setPortValue( Port *, float ) {};


        /**
         * Port range
         */

        virtual vector<float> getPortRange( Port * ) {

            vector<float> a;
            return a;

        };

        vector<float> getPortRange( unsigned int index ) {

            return getPortRange( _ports[ index ] );

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

        vector<long> * getControlPorts() {

            return &_controlPorts;

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
         * Getter helper for port index
         */

        vector<Port*> getPortsFromIndex( vector<long> * ports ) {

            vector<long>::iterator it;

            vector<Port*> output;

            for( it = ports->begin(); it != ports->end(); ++ it ) {

                output.push_back( getPort( (*it) ) );

            }

            return output;

        };


        /**
         * Stereo port getters
         * Will force mono to two places
         * @TODO create errors
         */

        vector<long> getInputPortsStereo() {

            vector<long> inputs;

            if( _inputs.size() > 1 ) {

                inputs.push_back( _inputs[ 0 ] );
                inputs.push_back( _inputs[ 1 ] );

            } else {

                inputs.push_back( _inputs[ 0 ] );
                inputs.push_back( _inputs[ 0 ] );

            }

            return inputs;

        };

        vector<long> getOutputPortsStereo() {

            vector<long> outputs;

            if( _outputs.size() > 1 ) {

                outputs.push_back( _outputs[ 0 ] );
                outputs.push_back( _outputs[ 1 ] );

            } else {

                outputs.push_back( _outputs[ 0 ] );
                outputs.push_back( _outputs[ 0 ] );

            }

            return outputs;

        };


        /**
         * Main virtuals
         */

        virtual void start() {};

        virtual void run() {};

        virtual void pause() {};

        virtual void stop() {};

        virtual Plugin * clone() {

            return new Plugin();

        };

    protected:

        /**
         * Shared props
         */

        bool ACTIVE = false;

        char id[255];

        char name[255];



        /**
         * Ports
         */

        uint32_t _portsNum;

        map<long, Port*> _ports;

        vector<long> _audioPorts;

        vector<long> _inputs;

        vector<long> _outputs;

        vector<long> _midiPorts;

        vector<long> _controlPorts;

        int long _numPorts;


        /**
         * UI
         * @TODO Possibly remove
         */

        UI * _UI;

};

};
