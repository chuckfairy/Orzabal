/**
 * Plugin worker jack processing h
 *
 */
#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include <lv2/lv2plug.in/ns/ext/worker/worker.h>

#include <lilv/lilv.h>

#include "include/symap.h"
#include "include/semaphone.h"
#include "include/zix_thread.c"

#include "PluginWorker.h"


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

        jack_ringbuffer_t * _requests;
        jack_ringbuffer_t * _responses;


        /**
         * Worker response buffer
         */

        void * _response;


        /**
         * Worker semaphore
         */

        ZixSem sem;


        /**
         * Worker thread
         */

        ZixThread _thread;


        /**
         * Plugin worker interface
         */

        const LV2_Worker_Interface* _iface;


        /**
         * Run work in another thread
         */

        bool _threaded;


        const uint32_t THREAD_BUFFER_SIZE = 4096;

        bool ACTIVE = false;


    public:

        PluginWorker( Plugin * );


        /**
         * Main initialize called from plugin
         */

        void init( LilvInstance *, bool threaded );


        /**
         * Finisher
         */

        void finish();


        /**
         * LV2 scheduler
         */

        static LV2_Worker_Status schedule(
            LV2_Worker_Schedule_Handle,
            uint32_t,
            const void *
        );


        /**
         * Main static response
         */

        static LV2_Worker_Status respond(
            LV2_Worker_Respond_Handle handle,
            uint32_t size,
            const void * data
        );

        static void * zixWork( void* data );

        void emitResponses( LilvInstance * );

        void emitIfaceEndRun( LV2_Handle );


        /**
         * Main thread flow, should be set from Plugin
         */

        bool isThreaded() {

            return _threaded;

        };


        /**
         * Main iface needs run emitter
         */

        bool hasIfaceRun();


        /**
         * Main getters
         */

        Plugin * getPlugin();


        /**
         * Jack ring buffer getters
         */

        jack_ringbuffer_t * getRequests() {

            return _requests;

        };

        jack_ringbuffer_t * getResponses() {

            return _responses;

        };


        /**
         * Zix sem
         */

        ZixSem getZixSem() {

            return sem;

        };

        const LV2_Worker_Interface * getIface() {

            return _iface;

        };

};

};
