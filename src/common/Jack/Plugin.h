/**
 * LV2 Plugin
 *
 */
#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include <Audio/Plugin.h>
#include <Audio/PlayState.h>

#include "Port.h"


namespace Jack {

/**
 * Plugin Main fro Audio::Plugin
 */

class Plugin : public Audio::Plugin {

    public:

        static const char * TYPE;


        /**
         * Jack virtual overloading for patchbay related
         */

        virtual void updateJack( jack_nframes_t ) {};

        virtual void updateJackLatency( jack_latency_callback_mode_t ) {};

        virtual void updateJackBufferSize( jack_nframes_t ) {};


        /**
         * virtual funcs
         */

        void start() {};

        void run() {};

        void pause() { ACTIVE = false; };

        void stop() {};

        virtual vector<float> getPortRange( Port * ) {

            vector<float> a;
            return a;

        };

        Audio::Plugin * clone() {

            return new Plugin();

        };

        const char * getType();

        Audio::UI * getUI() {

            return nullptr;

        };

        void setPortValue( Audio::Port * p, float value ) {};


        /**
         * Jack port getters helper
         */

        vector<jack_port_t*> getInputJackPorts() {

            vector<long> inputss = getInputPortsStereo();

            Port * portLeft = (Port*) getPort(
                inputss[ 0 ]
            );
            Port * portRight = (Port*) getPort(
                inputss[ 1 ]
            );

            vector<jack_port_t*> ports = {
                portLeft->jack_port,
                portRight->jack_port
            };

            return ports;

        };

        vector<jack_port_t*> getOutputJackPorts() {

            vector<long> outputs = getOutputPortsStereo();

            Port * portLeft = (Port*) getPort(
                outputs[ 0 ]
            );
            Port * portRight = (Port*) getPort(
                outputs[ 1 ]
            );

            vector<jack_port_t*> ports = {
                portLeft->jack_port,
                portRight->jack_port
            };

            return ports;

        };


    protected:

        jack_client_t * _jackClient;

};

};
