/**
 * LV2 Plugin
 *
 */
#include <string.h>
#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <Audio/Host.h>
#include <Audio/Port.h>

#include <lilv/lilv.h>

#include <jack/jack.h>
#include <jack/midiport.h>
#include <jack/session.h>
#include <jack/metadata.h>
#include <jack/ringbuffer.h>

#include "UI.h"
#include "include/symap.c"
#include "include/semaphone.h"
#include "Plugin.h"
#include "Port.h"
#include "Host.h"

#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#    define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif


using std::string;


namespace LV2 {


/**
 * Lilv plugin instance place
 */

Plugin::Plugin( const LilvPlugin* p, Host * h ) {

    setHost( h );

    setLilvPlugin( p );

};


/**
 * Set ports from lilv plugin
 * loops thru ports
 *
 */

void Plugin::setPorts() {

    long i;

    _defaultValues = (float*)calloc(
		lilv_plugin_get_num_ports( _lilvPlugin ), sizeof(float));

    lilv_plugin_get_port_ranges_float( _lilvPlugin, NULL, NULL, _defaultValues );

    _numPorts = lilv_plugin_get_num_ports( _lilvPlugin );

    for( int long i = 0; i < _numPorts; i++ ) {

        Audio::Port * port = createPort( i );

        setPort( i, port );

    }

};


/**
 * Lilv set plugin
 * sets name and other details
 *
 */

void Plugin::setLilvPlugin( const LilvPlugin * p ) {

    _lilvPlugin = p;

    LilvNode* n = lilv_plugin_get_name( _lilvPlugin );

    const char * nodeName = lilv_node_as_string( n );

    const char * uri = lilv_node_as_uri( lilv_plugin_get_uri( p ) );

    strcpy( _lilvURI, uri );

    setName( nodeName );

    lilv_node_free( n );

    setPorts();

};


/**
 * Create lv2 port num
 *
 */

Audio::Port * Plugin::createPort( int long portNum ) {

    Port * port = new LV2::Port();

    port->lilv_port = lilv_plugin_get_port_by_index( _lilvPlugin, portNum );

	port->jack_port = NULL;
    port->evbuf     = NULL;
	port->buf_size  = 0;
	port->index     = portNum;
	port->control   = 0.0f;
    port->flow = Audio::FLOW_UNKNOWN;

    const bool optional = portIsOptional( port );


	/* Set the port flow (input or output) */

	if( portIsInput( port ) ) {

		port->flow = Audio::FLOW_INPUT;

    } else if( portIsOutput( port ) ) {

        port->flow = Audio::FLOW_OUTPUT;

	} else if (!optional) {
		//die("Mandatory port has unknown type (neither input nor output)");
	}


	/* Set control values */

	if( portIsControl( port ) ) {

        port->type = Audio::TYPE_CONTROL;
        port->control = 0.0f;

	} else if( portIsAudio( port ) ) {

		port->type = Audio::TYPE_AUDIO;

    } else if( portIsCV( port ) ) {

		port->type = Audio::TYPE_CV;

	} else if( portIsEvent( port ) ) {

		port->type = Audio::TYPE_EVENT;
		port->old_api = true;

	} else if( portIsAtom( port ) ) {

		port->type = Audio::TYPE_EVENT;
		port->old_api = false;

	} else if (!optional) {
		//die("Mandatory port has unknown data type");
	}

    const LilvNode * rsz_minimumSize = lilv_new_uri( _lilvWorld, LV2_RESIZE_PORT__minimumSize );

	LilvNode* min_size = lilv_port_get( _lilvPlugin, port->lilv_port, rsz_minimumSize );
	if (min_size && lilv_node_is_int(min_size)) {
		port->buf_size = lilv_node_as_int(min_size);
        int buffer_size = MAX( buffer_size, port->buf_size * N_BUFFER_CYCLES );
	}

	lilv_node_free(min_size);


	/* Update longest symbol for aligned console printing */

	const LilvNode* sym = lilv_port_get_symbol( _lilvPlugin, port->lilv_port );
	const size_t len = strlen( lilv_node_as_string( sym ) );

	if (len > longest_sym) {

		longest_sym = len;

	}

    return port;

};


/**
 * LilvURI startup
 */

void Plugin::start() {

    std::cout << _lilvURI << "\n";

    _symap = symap_new();

    int block_size = 512;

    /* Build options array to pass to plugin */

    int uiUpdateHZ = 60;
    buffer_size = 4096;

    LV2_URID atom_Float = symap_map(_symap, LV2_ATOM__Float);
    LV2_URID atom_Int = symap_map(_symap, LV2_ATOM__Int);

    //jalv.urids.atom_Object          = symap_map(_symap, LV2_ATOM__Object);
    //jalv.urids.atom_Path            = symap_map(_symap, LV2_ATOM__Path);
    //jalv.urids.atom_String          = symap_map(_symap, LV2_ATOM__String);
    //jalv.urids.atom_eventTransfer   = symap_map(_symap, LV2_ATOM__eventTransfer);
    LV2_URID bufsz_maxBlockLength = symap_map(_symap, LV2_BUF_SIZE__maxBlockLength);
    LV2_URID bufsz_minBlockLength = symap_map(_symap, LV2_BUF_SIZE__minBlockLength);
    LV2_URID bufsz_sequenceSize = symap_map(_symap, LV2_BUF_SIZE__sequenceSize);
    //jalv.urids.log_Error            = symap_map(_symap, LV2_LOG__Error);
    //jalv.urids.log_Trace            = symap_map(_symap, LV2_LOG__Trace);
    //jalv.urids.log_Warning          = symap_map(_symap, LV2_LOG__Warning);
    LV2_URID param_sampleRate = symap_map(_symap, LV2_PARAMETERS__sampleRate);
    //jalv.urids.patch_Get            = symap_map(_symap, LV2_PATCH__Get);
    //jalv.urids.patch_Put            = symap_map(_symap, LV2_PATCH__Put);
    //jalv.urids.patch_Set            = symap_map(_symap, LV2_PATCH__Set);
    //jalv.urids.patch_body           = symap_map(_symap, LV2_PATCH__body);
    //jalv.urids.patch_property       = symap_map(_symap, LV2_PATCH__property);
    //jalv.urids.patch_value          = symap_map(_symap, LV2_PATCH__value);
    //jalv.urids.time_Position        = symap_map(_symap, LV2_TIME__Position);
    //jalv.urids.time_bar             = symap_map(_symap, LV2_TIME__bar);
    //jalv.urids.time_barBeat         = symap_map(_symap, LV2_TIME__barBeat);
    //jalv.urids.time_beatUnit        = symap_map(_symap, LV2_TIME__beatUnit);
    //jalv.urids.time_beatsPerBar     = symap_map(_symap, LV2_TIME__beatsPerBar);
    //jalv.urids.time_beatsPerMinute  = symap_map(_symap, LV2_TIME__beatsPerMinute);
    //jalv.urids.time_frame           = symap_map(_symap, LV2_TIME__frame);
    //jalv.urids.time_speed           = symap_map(_symap, LV2_TIME__speed);
    LV2_URID ui_updateRate = symap_map(_symap, LV2_UI__updateRate);
    LilvNode * work_interface = lilv_new_uri( _Host->getLilvWorld(), LV2_WORKER__interface );
    LilvNode * work_schedule = lilv_new_uri( _Host->getLilvWorld(), LV2_WORKER__schedule );

    int block_length = _Host->getBufferSize();

    int midi_buf_size = _Host->getMidiBufferSize();

    int sample_rate = _Host->getSampleRate();

    float ui_update_hz = (float)sample_rate / midi_buf_size * 2.0f;


    /* Build options array to pass to plugin */
    const LV2_Options_Option options[] = {
        {
            LV2_OPTIONS_INSTANCE, 0, param_sampleRate,
            sizeof(float), atom_Float, &sample_rate
        },
        {
            LV2_OPTIONS_INSTANCE, 0, bufsz_minBlockLength,
            sizeof(int32_t), atom_Int, &block_length
        },
        {
            LV2_OPTIONS_INSTANCE, 0, bufsz_maxBlockLength,
            sizeof(int32_t), atom_Int, &block_length
        },
        {
            LV2_OPTIONS_INSTANCE, 0, bufsz_sequenceSize,
            sizeof(int32_t), atom_Int, &midi_buf_size
        },
        {
            LV2_OPTIONS_INSTANCE, 0, ui_updateRate,
            sizeof(float), atom_Float, &ui_update_hz
        },
        { LV2_OPTIONS_INSTANCE, 0, 0, 0, 0, NULL }
    };


    //jalv_allocate_port_buffers(&jalv);

    /* Create workers if necessary */
    if( lilv_plugin_has_feature( _lilvPlugin, work_schedule )
            && lilv_plugin_has_extension_data(_lilvPlugin, work_interface)) {

        const LV2_Worker_Interface* iface = (const LV2_Worker_Interface*)
            lilv_instance_get_extension_data( _lilvInstance, LV2_WORKER__interface );

        //jalv_worker_init(&jalv, &jalv.worker, iface, true);
        //if (jalv.safe_restore) {
            //jalv_worker_init(&jalv, &jalv.state_worker, iface, false);
        //}
    }

    _ringBuffer = jack_ringbuffer_create(buffer_size);
	jack_ringbuffer_mlock( _ringBuffer );

    /* Instantiate the plugin */
    _lilvInstance = lilv_plugin_instantiate( _lilvPlugin, sample_rate, features );

    lilv_instance_activate( _lilvInstance );


    //Set descriptor

    _lilvDescriptor = lilv_instance_get_descriptor( _lilvInstance );

    if( ! _lilvInstance ) {
        //die("Failed to instantiate plugin.\n");
    }

    activatePorts();

    _UI = new UI( this );

    _UI->start();

    return;


    /* Apply loaded state to plugin instance if necessary */

    //if( state ) {
        //jalv_apply_state(&jalv, state);
    //}

    //if( jalv.opts.controls ) {
        //for( char** c = jalv.opts.controls; *c; ++c ) {
            //jalv_apply_control_arg(&jalv, *c);
        //}
    //}

    /* Set Jack callbacks */
    //jack_set_process_callback(jalv.jack_client,
            //&jack_process_cb, (void*)(&jalv));
    //jack_set_buffer_size_callback(jalv.jack_client,
            //&jack_buffer_size_cb, (void*)(&jalv));
    //jack_on_shutdown(jalv.jack_client,
            //&jack_shutdown_cb, (void*)(&jalv));
    //jack_set_latency_callback(jalv.jack_client,
            //&jack_latency_cb, (void*)(&jalv));
//#ifdef JALV_JACK_SESSION
    //jack_set_session_callback(jalv.jack_client,
            //&jack_session_cb, (void*)(&jalv));
//#endif

    /* Create Jack ports and connect plugin ports to buffers */
    //for (uint32_t i = 0; i < jalv.num_ports; ++i) {
        //activate_port(&jalv, i);
    //}


    /* Activate plugin */

    /* Run UI (or prompt at console) */
    //jalv_open_ui(&jalv);

    /* Wait for finish signal from UI or signal handler */
    zix_sem_wait(&exit_sem);



};


/**
 * LilvURI stop
 */

void Plugin::stop() {

    /* Terminate the worker */
    //jalv_worker_finish(&jalv.worker);

    /* Deactivate JACK */
    //for (uint32_t i = 0; i < numPorts; ++i) {
        //if (jalv.ports[i].evbuf) {
            //lv2_evbuf_free(jalv.ports[i].evbuf);
        //}
    //}

    /* Deactivate plugin */
    lilv_instance_deactivate( _lilvInstance );
    lilv_instance_free( _lilvInstance );

    /* Clean up */
//    jack_ringbuffer_free(jalv.ui_events);
//    jack_ringbuffer_free(jalv.plugin_events);

    symap_free( _symap );
    zix_sem_destroy( &_symap_lock );
    sratom_free( _sratom );
    //lilv_world_free(world);

    zix_sem_destroy( &exit_sem );

    remove( _tempDir );

};


/**
 * Port activations
 */

void Plugin::activatePorts() {

    for( long i = 0; i < _numPorts; i ++ ) {

        activatePort( i );

    }

};

void Plugin::activatePort( long portNum ) {

    Port * port = (Port*) _ports[ portNum ];

    const LilvNode* sym = lilv_port_get_symbol( _lilvPlugin, port->lilv_port );

    char nameChar[25];

    sprintf( nameChar, "%s:%s", name, lilv_node_as_string( sym ) );

    string name( nameChar );

    port->name = name.c_str();

    std::cout << "TEST\n" << port->name;


	/* Connect unsupported ports to NULL (known to be optional by this point) */

	if (port->flow == Audio::FLOW_UNKNOWN || port->type == Audio::TYPE_UNKNOWN) {
        lilv_instance_connect_port( _lilvInstance, portNum, NULL );
		return;
	}

	/* Build Jack flags for port */
	enum JackPortFlags jack_flags = (port->flow == Audio::FLOW_INPUT)
		? JackPortIsInput
		: JackPortIsOutput;

    jack_client_t * jack_client = _Host->getJackClient();

    const LilvNode * midi_MidiEvent = lilv_new_uri( _lilvWorld, LV2_MIDI__MidiEvent );

	/* Connect the port based on its type */

    switch( port->type ) {

        case Audio::TYPE_CONTROL:
            lilv_instance_connect_port( _lilvInstance, portNum, &port->control);
            break;

        case Audio::TYPE_AUDIO:
            port->jack_port = jack_port_register(
                    jack_client, port->name,
                    JACK_DEFAULT_AUDIO_TYPE, jack_flags, 0);
            break;

        case Audio::TYPE_CV:
            port->jack_port = jack_port_register(
                    jack_client, port->name,
                    JACK_DEFAULT_AUDIO_TYPE, jack_flags, 0);
            if (port->jack_port) {
                jack_set_property(jack_client, jack_port_uuid(port->jack_port),
                        "http://jackaudio.org/metadata/signal-type", "CV",
                        "text/plain");
            }
            break;

        case Audio::TYPE_EVENT:
            if( lilv_port_supports_event(
                        _lilvPlugin, port->lilv_port, midi_MidiEvent ) ) {
                port->jack_port = jack_port_register(
                        jack_client, port->name,
                        JACK_DEFAULT_MIDI_TYPE, jack_flags, 0);
            }
            break;

        default: case Audio::TYPE_UNKNOWN:
            break;

    }

	if (port->jack_port) {

		// Set port order to index
		char index_str[16];

        snprintf(index_str, sizeof(index_str), "%d", (int)portNum);

		jack_set_property(
            jack_client,
            jack_port_uuid(port->jack_port),
            "http://jackaudio.org/metadata/order",
            index_str,
            "http://www.w3.org/2001/XMLSchema#integer"
        );

		// Set port pretty name to label
		LilvNode* name = lilv_port_get_name(_lilvPlugin, port->lilv_port);

		jack_set_property(
            jack_client,
            jack_port_uuid(port->jack_port),
            JACK_METADATA_PRETTY_NAME,
            lilv_node_as_string(name),
            "text/plain"
        );

		lilv_node_free(name);

	}

}


/**
 * UI
 */

UI * Plugin::getUI() {

    return _UI;

};


/**
 * UI
 */

QScrollArea * Plugin::getUIWidget() {

    return _UI->getWidget();

};


/**
 * Port type methods
 */

const bool Plugin::portIs( Port * p, const char * type ) {

    LilvNode * opt = lilv_new_uri( _lilvWorld, type );

    const bool output = lilv_port_is_a( _lilvPlugin, p->lilv_port, opt );

    lilv_node_free( opt );

    return output;

};

const bool Plugin::portIsOptional( Port * p ) {

    LilvNode * connectionOptional = lilv_new_uri(
        _lilvWorld,
        LV2_CORE__connectionOptional
    );

    const bool output = lilv_port_has_property( _lilvPlugin, p->lilv_port, connectionOptional );

    lilv_node_free( connectionOptional );

    return output;

};

const bool Plugin::portIsAudio( Port * p ) {

    return portIs( p, LV2_CORE__AudioPort );

};

const bool Plugin::portIsInput( Port * p ) {

    return portIs( p, LV2_CORE__InputPort );

};

const bool Plugin::portIsOutput( Port * p ) {

    return portIs( p, LV2_CORE__OutputPort );

};

const bool Plugin::portIsControl( Port * p ) {

    return portIs( p, LV2_CORE__ControlPort );

};

const bool Plugin::portIsEvent( Port * p ) {

    return portIs( p, LV2_EVENT__EventPort );

};

const bool Plugin::portIsAtom( Port * p ) {

    return portIs( p, LV2_ATOM__AtomPort );

};

const bool Plugin::portIsCV( Port * p ) {

    return portIs( p, LV2_CORE__CVPort );

};

};
