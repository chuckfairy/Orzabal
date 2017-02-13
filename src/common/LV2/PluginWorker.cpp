/**
 * Plugin worker jack processing h
 */
#include <cstdlib>

#include "Plugin.h"
#include "PluginWorker.h"


namespace LV2 {

/**
 * Construct
 */

PluginWorker::PluginWorker( Plugin * p ) {

    _Plugin = p;

	zix_sem_init( &sem, 0 );

};


/**
 * Plugin impl getter
 */

Plugin * PluginWorker::getPlugin() {

    return _Plugin;

}


/**
 * Main responder
 */

LV2_Worker_Status PluginWorker::respond(
    LV2_Worker_Respond_Handle handle,
    uint32_t size,
    const void * data
) {

    std::cout << "WORKER \n";

    PluginWorker* worker = (PluginWorker*)handle;

    jack_ringbuffer_t * res = worker->getResponses();

    jack_ringbuffer_write( res, (const char*) &size, sizeof( size ) );

    jack_ringbuffer_write( res, (const char*) data, size);

    return LV2_WORKER_SUCCESS;

};


/**
 * Zix worker static
 */

void * PluginWorker::zixWork(void* data) {

    PluginWorker * worker = (PluginWorker*) data;
    Plugin * plugin = worker->getPlugin();
    void* buf = NULL;

    ZixSem sem = worker->getZixSem();

    while( true ) {

        zix_sem_wait( &sem );

        if( ! plugin->isActive() ) {
            break;
        }

        uint32_t size = 0;

        jack_ringbuffer_read(
            worker->getRequests(),
            (char*) &size,
            sizeof( size )
        );

        if ( ! ( buf = realloc( buf, size ) ) ) {

            fprintf(stderr, "error: realloc() failed\n");
            free(buf);
            return NULL;

        }

        jack_ringbuffer_read(
            worker->getRequests(),
            (char*) buf,
            size
        );

        ZixSem workerLock = worker->getPlugin()->getWorkerLock();

        zix_sem_wait( &workerLock );

        const LV2_Worker_Interface* iface = worker->getIface();

        iface->work(
            plugin->getLV2Handle(),
            PluginWorker::respond,
            worker,
            size,
            buf
        );

        zix_sem_post( &workerLock );

    }

    free( buf );

    return NULL;

};


/**
 * Main init
 */

void PluginWorker::init( LilvInstance * instance, bool threaded ) {


    _iface = (const LV2_Worker_Interface*)
        lilv_instance_get_extension_data( instance, LV2_WORKER__interface );

    _threaded = threaded;

    if( _threaded ) {

        zix_thread_create( &_thread, THREAD_BUFFER_SIZE, PluginWorker::zixWork, this );
        _requests = jack_ringbuffer_create( THREAD_BUFFER_SIZE );
        jack_ringbuffer_mlock( _requests );

    }

    _responses = jack_ringbuffer_create( THREAD_BUFFER_SIZE );
    _response  = malloc( THREAD_BUFFER_SIZE );

    jack_ringbuffer_mlock( _responses );

    ACTIVE = true;

};


/**
 * Worker finisher
 */

void PluginWorker::finish() {

    if( ! ACTIVE || ! _requests ) {

        return;

    }

    if( _threaded ) {

        zix_sem_post( &sem );
        zix_thread_join( _thread, NULL );
        jack_ringbuffer_free( _requests );

    }

    jack_ringbuffer_free( _responses );
    free( _response );

};


/**
 * Main scheduler
 */

LV2_Worker_Status PluginWorker::schedule(
    LV2_Worker_Schedule_Handle handle,
    uint32_t size,
    const void * data
) {

    PluginWorker * worker = (PluginWorker*) handle;

    Plugin * plugin = worker->getPlugin();

    if( worker->isThreaded() ) {

        jack_ringbuffer_t * requests = worker->getRequests();

        // Schedule a request to be executed by the worker thread
        jack_ringbuffer_write(
            requests,
            (const char*) &size,
            sizeof(size)
        );

        jack_ringbuffer_write( requests, (const char*) data, size );


        //Zix sem setup

        ZixSem sem = worker->getZixSem();

        zix_sem_post( &sem );

    } else {

        // Execute work immediately in this thread

        ZixSem workerLock = plugin->getWorkerLock();

        zix_sem_wait( &workerLock );

        const LV2_Worker_Interface* iface = worker->getIface();

        iface->work(
            plugin->getLV2Handle(),
            PluginWorker::respond,
            worker,
            size,
            data
        );

        zix_sem_post( &workerLock );

    }

    return LV2_WORKER_SUCCESS;

};


/**
 * Plubic emitter of all responses on ring buffer space
 */

void PluginWorker::emitResponses( LilvInstance * instance ) {

    if( ! ACTIVE || ! _responses ) {

        return;

    }

    uint32_t read_space = jack_ringbuffer_read_space( _responses );

    while( read_space ) {

        uint32_t size = 0;

        jack_ringbuffer_read( _responses, (char*) &size, sizeof( size ) );

        jack_ringbuffer_read( _responses, (char*) _response, size );

        _iface->work_response( instance->lv2_handle, size, _response );

        read_space -= sizeof( size ) + size;

    }

};


/**
 * Worker iface related
 */

bool PluginWorker::hasIfaceRun() {

    return ( ACTIVE && _Plugin->isActive() && _iface );

};


void PluginWorker::emitIfaceEndRun( LV2_Handle handle ) {

    _iface->end_run( handle );

};

};
