/**
 * LV2 Plugin
 *
 */
#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include <Audio/Plugin.h>
#include <Audio/PlayState.h>


#define NS_EXT "http://lv2plug.in/ns/ext/"


namespace Jack {

/**
 * Plugin Main fro Audio::Plugin
 */

class Plugin : public Audio::Plugin {

    public:

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

        void pause() {};

        void stop() {};

};

};
