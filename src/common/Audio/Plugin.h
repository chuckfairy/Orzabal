/**
 * Plugin abstract
 *
 */
#pragma once

#include "Port.h"

#include <vector>
#include <map>

using std::vector;
using std::map;


/**
 * LADSPA plugin class
 *
 */

class Plugin {

    protected:

        Plugin();

        bool ACTIVE = false;

        virtual char[10] TYPE = 0;

        map<long, Port> _ports;

        vector<long> _audioPorts;

        vector<long> _inputs;

        vector<long> _outputs;

        vector<long> _controlPorts;

        char name[255];


    public:

        /**
         * Get type
         *
         */

        char[10] * getType() {

            return &TYPE;

        };


        /**
         * Inputs grabbed from ports
         *
         */

        vector<long> * getInputs() {

            return &_inputs;

        };


        /**
         * Get output long ports
         *
         */

        vector<long> * getOutputs() {

            return &_outputs;

        };


        /**
         * Get name of plugin
         * From _descriptor
         *
         */

        const char * getName() {

            return name;

        };


        /**
         * Is on / connected
         *
         */

        bool isActive() {

            return ACTIVE;

        };


        /**
         * Set ports from Descriptor
         *
         */

        virtual void setPorts();


        /**
         * Map and set port
         *
         */

        void setPort( long index, Port port );


        /**
         * Create a port
         *
         */

        virtual Port createPort( long portNum );

};
