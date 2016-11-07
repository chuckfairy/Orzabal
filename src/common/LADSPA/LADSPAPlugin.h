/**
 * Plugin class
 *
 */
#pragma once

#include <vector>
#include <map>

#include "ladspa.h"

#include "LADSPAPort.h"


using std::vector;
using std::map;


/**
 * LADSPA plugin class
 *
 */

class LADSPAPlugin {

    private:

        const LADSPA_Descriptor * _descriptor;

        bool ACTIVE = false;

        map<long, LADSPAPort> _ports;

        vector<long> _audioPorts;

        vector<long> _inputs;

        vector<long> _outputs;

        vector<long> _controlPorts;

        char name[250];


    public:

        LADSPAPlugin( const LADSPA_Descriptor * des );


        /**
         * Set descriptor
         *
         */

        void setDescriptor( const LADSPA_Descriptor * des );


        /**
         * Get private descriptor
         * for raw stuff
         *
         */

        const LADSPA_Descriptor * getDescriptor() {

            return _descriptor;

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

            //return "TEST";
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

        void setPorts();


        /**
         * Map and set port
         *
         */

        void setPort( long index, LADSPAPort port );


        /**
         * Create a port
         *
         */

        LADSPAPort createPort( long portNum );

};
