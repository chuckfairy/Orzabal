/**
 * Plugin worker jack processing h
 */
#pragma once

#include <lv2/lv2plug.in/ns/ext/worker/worker.h>


namespace LV2 {

/**
 *  Forwarding
 */

class Plugin;


/**
 * Base
 */

class PluginWorker {

    private:

        Plugin * _Plugin;


        /**
         * Requests and response via jack
         */

        jack_ringbuffer_t * requests;
        jack_ringbuffer_t * responses;


        /**
         * Worker response buffer
         */

        void* response;


        /**
         * Worker semaphore
         */

        ZixSem sem;


        /**
         * Worker thread
         */

        ZixThread thread;


        /**
         * Plugin worker interface
         */

        const LV2_Worker_Interface* iface;


        /**
         * Run work in another thread
         */

        bool threaded;


    public:

        PluginWorker( Plugin * );

        /**
         * Finisher
         */

        void finish();


        /**
         * LV2 scheduler
         */

        LV2_Worker_Status schedule(
            LV2_Worker_Schedule_Handle,
            uint32_t,
            const void *
        );

};

};
