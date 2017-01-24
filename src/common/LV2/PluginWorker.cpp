/**
 * Plugin worker jack processing h
 */

#include "PluginWorker.h"

namespace LV2 {

/**
 * Construct
 */

PluginWorker::PluginWorker( Plugin * p ) {

    _Plugin = p;

};


/**
 * Main responder
 */

LV2_Worker_Status PluginWorker::respond(
    LV2_Worker_Respond_Handle handle,
    uint32_t                  size,
    const void*               data
) {

    PluginWorker* worker = (PluginWorker*)handle;
    jack_ringbuffer_write( worker->responses, (const char*) &size, sizeof( size ) );
    jack_ringbuffer_write( worker->responses, (const char*) data, size );
    return LV2_WORKER_SUCCESS;

};


/**
 * Zix worker static
 */

void * PluginWorker::zixWork(void* data) {

    PluginWorker * worker = (JalvWorker*)data;
    Jalv* jalv = worker->jalv;
    void* buf = NULL;

    while( true ) {

        zix_sem_wait(&worker->sem);

        if (jalv->exit) {
            break;
        }

        uint32_t size = 0;
        jack_ringbuffer_read(worker->requests, (char*)&size, sizeof(size));

        if (!(buf = realloc(buf, size))) {
            fprintf(stderr, "error: realloc() failed\n");
            free(buf);
            return NULL;
        }

        jack_ringbuffer_read(worker->requests, (char*)buf, size);

        zix_sem_wait(&jalv->work_lock);

        worker->iface->work(
            jalv->instance->lv2_handle,
            jalv_worker_respond,
            worker,
            size,
            buf
        );

        zix_sem_post( _Plugin->work_lock );

    }

    free( buf );

    return NULL;

};


/**
 * Main init
 */

void PluginWorker::init( const LV2_Worker_Interface* ifaceInit, bool threaded ) {

    _iface = iface;
    _threaded = threaded;

    if( _threaded ) {

        zix_thread_create( &_thread, 4096, Plugin::zixWork, this );
        _requests = jack_ringbuffer_create( 4096 );
        jack_ringbuffer_mlock( _requests );

    }

    _responses = jack_ringbuffer_create( 4096 );
    _response  = malloc( 4096 );

    jack_ringbuffer_mlock( _responses );

};


/**
 * Worker finisher
 */

void PluginWorker::finish() {

    if( !requests ) {

        return;

    }

    if( threaded ) {

        zix_sem_post( &sem );
        zix_thread_join( thread, NULL );
        jack_ringbuffer_free( requests );

    }

    jack_ringbuffer_free( responses );
    free(worker->response);

}:


/**
 * Main scheduler
 */

LV2_Worker_Status PluginWorker::schedule(
    LV2_Worker_Schedule_Handle handle,
    uint32_t size,
    const void * data
) {

    PluginWorker * worker = (PluginWorker*) handle;

    Plugin * jalv = _Plugin;

    if( worker->threaded ) {

        // Schedule a request to be executed by the worker thread
        jack_ringbuffer_write(
            _requests,
            (const char*)&size,
            sizeof(size)
        );

        jack_ringbuffer_write( _requests, (const char*)data, size );
        zix_sem_post( &sem );

    } else {
        // Execute work immediately in this thread
        zix_sem_wait(&jalv->work_lock);
        worker->iface->work(
                jalv->instance->lv2_handle, jalv_worker_respond, worker, size, data);
        zix_sem_post(&jalv->work_lock);
    }

    return LV2_WORKER_SUCCESS;

};


/**
 * Plubic emitter of all responses on ring buffer space
 */

void PluginWorker::emitResponses( JalvWorker* worker, LilvInstance* instance ) {

    if( worker->responses ) {

        uint32_t read_space = jack_ringbuffer_read_space( _responses );

        while( read_space ) {

            uint32_t size = 0;

            jack_ringbuffer_read( _responses, (char*) &size, sizeof( size ) );

            jack_ringbuffer_read( _responses, (char*) _response, size );

            worker->iface->work_response( instance->lv2_handle, size, _response );

            read_space -= sizeof(size) + size;

        }

    }

};

};
