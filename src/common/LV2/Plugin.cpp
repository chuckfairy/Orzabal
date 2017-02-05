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
#include "include/lv2_evbuf.h"
#include "PluginWorker.h"
#include "Plugin.h"
#include "Port.h"
#include "ControlChange.h"
#include "Host.h"

//@TODO move to std::max
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

    _worker = new PluginWorker( this );

};


/**
 * Set ports from lilv plugin
 * loops thru ports
 *
 */

void Plugin::setPorts() {

    long i;

    _defaultValues = (float*)calloc(
        lilv_plugin_get_num_ports( _lilvPlugin ),
        sizeof( float )
    );

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
 * @throws runtime_error Port malfunction
 *
 */

Audio::Port * Plugin::createPort( int long portNum ) {

    Port * port = new LV2::Port();

    port->lilv_port = lilv_plugin_get_port_by_index( _lilvPlugin, portNum );

	port->jack_port = NULL;
    port->evbuf = NULL;
	port->buf_size  = 0;
	port->index = portNum;
	port->control = 0.0f;
    port->flow = Audio::FLOW_UNKNOWN;

    const bool optional = portIsOptional( port );


	/* Set the port flow (input or output) */

	if( portIsInput( port ) ) {

		port->flow = Audio::FLOW_INPUT;

    } else if( portIsOutput( port ) ) {

        port->flow = Audio::FLOW_OUTPUT;

	} else if (!optional) {

        throw std::runtime_error( "Port not optional, but not IO" );

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

	} else if( !optional ) {

        throw std::runtime_error(
            "Mandatory port has unknown data type"
        );

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

    _symap = symap_new();


    /* Build options array to pass to plugin */

    int uiUpdateHZ = 60;
    buffer_size = 4096;

	zix_sem_init( &symap_lock, 1 );
	zix_sem_init( &exit_sem, 0 );

    uri_map_feature.data  = &uri_map;
    uri_map.callback_data = this;

    //Map setup

    map.handle = this;
    map.map = Plugin::mapURI;

    map_feature.data = &map;

    unmap.handle = this;
    unmap.unmap = Plugin::unmapURI;
    unmap_feature.data = &unmap;

    lv2_atom_forge_init(&_forge, &map);


    //URI and symap creation
    //@TODO definitely move

    LV2_URID atom_Float = symap_map(_symap, LV2_ATOM__Float);
    LV2_URID atom_Int = symap_map(_symap, LV2_ATOM__Int);

    midi_event_id = Plugin::uriToId(
        this,
        "http://lv2plug.in/ns/ext/event",
        LV2_MIDI__MidiEvent
    );

    atom_Object = symap_map(_symap, LV2_ATOM__Object);
    //jalv.urids.atom_Path            = symap_map(_symap, LV2_ATOM__Path);
    //jalv.urids.atom_String          = symap_map(_symap, LV2_ATOM__String);

    atom_eventTransfer = symap_map(_symap, LV2_ATOM__eventTransfer);

	atom_Chunk = lilv_new_uri( _Host->getLilvWorld(), LV2_ATOM__Chunk );
	atom_Sequence = lilv_new_uri( _Host->getLilvWorld(), LV2_ATOM__Sequence );

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
    patch_Get = symap_map(_symap, LV2_PATCH__Get);

    _time_position = symap_map(_symap, LV2_TIME__Position);
    _time_bar = symap_map(_symap, LV2_TIME__bar);
    _time_barBeat = symap_map(_symap, LV2_TIME__barBeat);
    _time_beatUnit = symap_map(_symap, LV2_TIME__beatUnit);
    _time_beatsPerBar = symap_map(_symap, LV2_TIME__beatsPerBar);
    _time_beatsPerMinute  = symap_map(_symap, LV2_TIME__beatsPerMinute);
    _time_frame = symap_map(_symap, LV2_TIME__frame);
    _time_speed = symap_map(_symap, LV2_TIME__speed);

    //@ENDTODO

	LV2_State_Make_Path make_path = { this, Plugin::LV2MakePath };
	make_path_feature.data = &make_path;

	LV2_Worker_Schedule sched = { &_worker, PluginWorker::schedule };
    sched_feature.data = &sched;

    LV2_URID ui_updateRate = symap_map(_symap, LV2_UI__updateRate);
    LilvNode * work_interface = lilv_new_uri( _Host->getLilvWorld(), LV2_WORKER__interface );
    LilvNode * work_schedule = lilv_new_uri( _Host->getLilvWorld(), LV2_WORKER__schedule );


    //Buffer and data setting

    lv2_reportsLatency = lilv_new_uri( _Host->getLilvWorld(), LV2_CORE__reportsLatency );

    block_length = _Host->getBufferSize();

    midi_buf_size = _Host->getMidiBufferSize();

    sample_rate = _Host->getSampleRate();

    ui_update_hz = (float) sample_rate / midi_buf_size * 2.0f;


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

	options_feature.data = (void*) &options;


    //Allocate jack bufs

    _ringBuffer = jack_ringbuffer_create(buffer_size);
	jack_ringbuffer_mlock( _ringBuffer );

    /* Instantiate the plugin */
    _lilvInstance = lilv_plugin_instantiate( _lilvPlugin, sample_rate, features );

    lilv_instance_activate( _lilvInstance );

    allocatePortBuffers();


    /* Create workers if necessary */

    if( lilv_plugin_has_feature( _lilvPlugin, work_schedule )
            && lilv_plugin_has_extension_data(_lilvPlugin, work_interface)) {

        _worker->init( _lilvInstance, true );

        //@TODO Implement save reloading
        //if (safe_restore) {
            //jalv_worker_init(&jalv, &jalv.state_worker, iface, false);
        //}
    }


    //Set descriptor

    _lilvDescriptor = lilv_instance_get_descriptor( _lilvInstance );

    if( ! _lilvInstance ) {

        throw std::runtime_error( "Plugin could not instaniate" );

    }

    activatePorts();

    _UI = new UI( this );

    _UI->start();

    //if( jalv.opts.controls ) {
        //for( char** c = jalv.opts.controls; *c; ++c ) {
            //jalv_apply_control_arg(&jalv, *c);
        //}
    //}
    /* Wait for finish signal from UI or signal handler */

};


/**
 * Main thread run
 */

void Plugin::run() {

    ACTIVE = true;


    //@TODO determine sem flow or thread/atomic alternative
    zix_sem_wait(&exit_sem);

};

/**
 * LilvURI stop
 */

void Plugin::stop() {

    /* Terminate the worker */

    _worker->finish();

    /* @TODO Deactivate JACK */
    //for (uint32_t i = 0; i < numPorts; ++i) {
        //if (jalv.ports[i].evbuf) {
            //lv2_evbuf_free(jalv.ports[i].evbuf);
        //}
    //}

    /* Deactivate plugin */
    lilv_instance_deactivate( _lilvInstance );
    lilv_instance_free( _lilvInstance );

    jack_ringbuffer_free( _ringBuffer );

    symap_free( _symap );
    zix_sem_destroy( &_symap_lock );
    //lilv_world_free(world);

    zix_sem_destroy( &exit_sem );

    //remove( _tempDir );

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

    std::cout << "\n" << port->name;


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

                jack_set_property(
                    jack_client,
                    jack_port_uuid(port->jack_port),
                    "http://jackaudio.org/metadata/signal-type",
                    "CV",
                    "text/plain"
                );

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

};


/**
 * Allocate port buffers (only necessary for MIDI).
 */

void Plugin::allocatePortBuffers() {

	for( uint32_t i = 0; i < _numPorts; ++i ) {

        allocatePortBuffer( i );

    }

}

void Plugin::allocatePortBuffer( uint32_t i ) {

    Port* port = (Port*) _ports[ i ];

    switch( port->type ) {

        case Audio::TYPE_EVENT: {

            lv2_evbuf_free( port->evbuf );

            const size_t buf_size = port->buf_size > 0
                ? port->buf_size
                : midi_buf_size;

            port->evbuf = lv2_evbuf_new(
                buf_size,
                port->old_api ? LV2_EVBUF_EVENT : LV2_EVBUF_ATOM,
                map.map(
                    map.handle,
                    lilv_node_as_string( atom_Chunk )
                ),
                map.map(
                    map.handle,
                    lilv_node_as_string( atom_Sequence )
                )
            );

            lilv_instance_connect_port(
                _lilvInstance,
                i,
                lv2_evbuf_get_buffer( port->evbuf )
            );
            break;

        }

        default:
            break;

    }

};


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
 * Get LV2 Handle from instalce
 */

LV2_Handle Plugin::getLV2Handle() {

    return _lilvInstance->lv2_handle;

};


/**
 *
 */

void Plugin::updateJack( jack_nframes_t nframes ) {

	/* Get Jack transport position */

    std::cout << "NFRAMES " << nframes << "\n";

    jack_client_t * jackClient = _Host->getJackClient();

    jack_position_t pos;

    const bool rolling = (
        jack_transport_query( jackClient, &pos ) == JackTransportRolling
    );

    /* If transport state is not as expected, then something has changed */
    xport_changed = (rolling != _transportRolling ||
            pos.frame != _position ||
            pos.beats_per_minute != _bpm);

    uint8_t   pos_buf[256];
    lv2_pos = (LV2_Atom*)pos_buf;

    if( xport_changed ) {

        /* Build an LV2 position object to report change to plugin */
        lv2_atom_forge_set_buffer(&_forge, pos_buf, sizeof(pos_buf));
        LV2_Atom_Forge* forge = &_forge;
        LV2_Atom_Forge_Frame frame;
        lv2_atom_forge_object(forge, &frame, 0, _time_position);
        lv2_atom_forge_key(forge, _time_frame);
        lv2_atom_forge_long(forge, pos.frame);
        lv2_atom_forge_key(forge, _time_speed);
        lv2_atom_forge_float(forge, rolling ? 1.0 : 0.0);

        if (pos.valid & JackPositionBBT) {

            lv2_atom_forge_key(forge, _time_barBeat);
            lv2_atom_forge_float(
                    forge, pos.beat - 1 + (pos.tick / pos.ticks_per_beat));
            lv2_atom_forge_key(forge, _time_bar);
            lv2_atom_forge_long(forge, pos.bar - 1);
            lv2_atom_forge_key(forge, _time_beatUnit);
            lv2_atom_forge_int(forge, pos.beat_type);
            lv2_atom_forge_key(forge, _time_beatsPerBar);
            lv2_atom_forge_float(forge, pos.beats_per_bar);
            lv2_atom_forge_key(forge, _time_beatsPerMinute);
            lv2_atom_forge_float(forge, pos.beats_per_minute);

        }

    }


    /* Update transport state to expected values for next cycle */

    _position = rolling ? pos.frame + nframes : pos.frame;
    _bpm = pos.beats_per_minute;
    _transportRolling  = rolling;

    LV2_URID param_sampleRate = symap_map(_symap, LV2_PARAMETERS__sampleRate);


    /* Prepare port buffers */

    for( uint32_t p = 0; p < _numPorts; ++ p ) {

        updatePort( p, nframes );

    }

    _request_update = false;


    /* Read and apply control change events from UI */

    if( _UI && false ) {

        ControlChange ev;

        jack_ringbuffer_t * ui_events = _UI->getPortEvents();

        const size_t readSpace = jack_ringbuffer_read_space( ui_events );

        for( size_t i = 0; i < readSpace; i += sizeof(ev) + ev.size ) {

            jack_ringbuffer_read(ui_events, (char*)&ev, sizeof(ev));
            char body[ev.size];

            if (jack_ringbuffer_read(ui_events, body, ev.size) != ev.size) {
                fprintf(stderr, "error: Error reading from UI ring buffer\n");
                break;
            }

            //assert(ev.index < jalv->num_ports);

            Port * port = (Port*) _ports[ev.index];

            if (ev.protocol == 0) {
                assert(ev.size == sizeof(float));
                port->control = *(float*)body;
            } else if (ev.protocol == atom_eventTransfer) {
                LV2_Evbuf_Iterator    e    = lv2_evbuf_end(port->evbuf);
                const LV2_Atom* const atom = (const LV2_Atom*)body;
                lv2_evbuf_write(
                    &e,
                    nframes,
                    0,
                    atom->type,
                    atom->size,
                    (const uint8_t*) LV2_ATOM_BODY_CONST(atom)
                );

            } else {

                throw std::runtime_error(
                    "error: Unknown control change protocol %d\n"
                    //ev.protocol);
                );

            }

        }

    }

    /* Run plugin for this cycle */
    lilv_instance_run(_lilvInstance, nframes);

	/* Process any worker replies. */
    _worker->emitResponses( _lilvInstance );

    //@TODO Implement saved state
	//_stateWorker->emitResponses( _lilvInstance );

    /* Notify the plugin the run() cycle is finished */
    if ( _worker->hasIfaceRun() ) {

        _worker->emitIfaceEndRun( _lilvInstance->lv2_handle );

    }


    /* Check if it's time to send updates to the UI */
    event_delta_t += nframes;
    bool send_ui_updates = false;
    jack_nframes_t update_frames = sample_rate / ui_update_hz;

    if ( _UI && (event_delta_t > update_frames) ) {
        send_ui_updates = true;
        event_delta_t = 0;
    }

    /* Deliver MIDI output and UI events */
    for (uint32_t p = 0; p < _numPorts; ++p) {

        Port * port = (Port*) _ports[ p ];

        if(
            port->flow == Audio::FLOW_OUTPUT
            && port->type == Audio::TYPE_CONTROL
            && lilv_port_has_property(
                _lilvPlugin,
                port->lilv_port,
                lv2_reportsLatency
            )
        ) {

            if (plugin_latency != port->control) {

                plugin_latency = port->control;

                jack_recompute_total_latencies( jackClient );

            }

        }

        if (port->flow == Audio::FLOW_OUTPUT && port->type == Audio::TYPE_EVENT) {

            void* buf = NULL;

            std::cout << "Any Flow Pleas\n";

            if (port->jack_port) {
                buf = jack_port_get_buffer(port->jack_port, nframes);
                jack_midi_clear_buffer(buf);
            }

            for( LV2_Evbuf_Iterator i = lv2_evbuf_begin(port->evbuf);
                    lv2_evbuf_is_valid(i);
                    i = lv2_evbuf_next(i)
            ) {
                uint32_t frames, subframes, type, size;
                uint8_t* body;
                lv2_evbuf_get(i, &frames, &subframes, &type, &size, &body);
                if (buf && type == midi_event_id) {
                    std::cout << "Midi Event Huzzah\n";
                    jack_midi_event_write(buf, frames, body, size);
                }


                /* TODO: Be more disciminate about what to send */

                if( _UI  && ! port->old_api ) {

                    char evbuf[sizeof(ControlChange) + sizeof(LV2_Atom)];
                    ControlChange* ev = (ControlChange*)evbuf;
                    ev->index = p;
                    ev->protocol = atom_eventTransfer;
                    ev->size = sizeof(LV2_Atom) + size;
                    LV2_Atom* atom = (LV2_Atom*)ev->body;
                    atom->type = type;
                    atom->size = size;

                    if( jack_ringbuffer_write_space( _ringBuffer )
                            < sizeof(evbuf) + size
                    ) {
                        fprintf(stderr, "Plugin => UI buffer overflow!\n");
                        break;
                    }

                    jack_ringbuffer_write(_ringBuffer, evbuf, sizeof(evbuf));
                    /* TODO: race, ensure reader handles this correctly */
                    jack_ringbuffer_write(_ringBuffer, (const char*)body, size);

                }

            }

        } else if (send_ui_updates
                && port->flow != Audio::FLOW_INPUT
                && port->type == Audio::TYPE_CONTROL) {

            char buf[sizeof(ControlChange) + sizeof(float)];
            ControlChange* ev = (ControlChange*)buf;
            ev->index    = p;
            ev->protocol = 0;
            ev->size     = sizeof(float);
            *(float*)ev->body = port->control;

            if (jack_ringbuffer_write(_ringBuffer, buf, sizeof(buf))
                    < sizeof(buf)) {
                fprintf(stderr, "Plugin => UI buffer overflow!\n");
            }

        }

    }

};


/**
 * Jack latency callback
 */

void Plugin::updateJackLatency( jack_latency_callback_mode_t mode ) {

    const enum Audio::PortFlow flow = ((mode == JackCaptureLatency)
        ? Audio::FLOW_INPUT :
        Audio::FLOW_OUTPUT);

	/* First calculate the min/max latency of all feeding ports */
	uint32_t             ports_found = 0;
	jack_latency_range_t range       = { UINT32_MAX, 0 };
	for (uint32_t p = 0; p < _numPorts; ++p) {

		Port * port = (Port*) _ports[p];

		if (port->jack_port && port->flow == flow) {

			jack_latency_range_t r;
			jack_port_get_latency_range(port->jack_port, mode, &r);
			if(r.min < range.min) { range.min = r.min; }
			if(r.max > range.max) { range.max = r.max; }
			++ports_found;

		}

	}


	if (ports_found == 0) {
		range.min = 0;
	}

	/* Add the plugin's own latency */
	range.min += plugin_latency;
	range.max += plugin_latency;

	/* Tell Jack about it */
	for (uint32_t p = 0; p < _numPorts; ++p) {

		Port * port = (Port*) _ports[p];

		if( port->jack_port && port->flow == flow ) {

			jack_port_set_latency_range(port->jack_port, mode, &range);

		}

	}

};


/**
 * Update lv2 to jack port
 */

void Plugin::updatePort( uint32_t p, jack_nframes_t nframes ) {

    Port * port = (Port*) _ports[ p ];

    if( port->type == Audio::TYPE_AUDIO && port->jack_port ) {

        /* Connect plugin port directly to Jack port buffer */
        lilv_instance_connect_port(
            _lilvInstance,
            p,
            jack_port_get_buffer( port->jack_port, nframes )
        );

    } else if( port->type == Audio::TYPE_CV && port->jack_port ) {

        /* Connect plugin port directly to Jack port buffer */
        lilv_instance_connect_port(
            _lilvInstance, p,
            jack_port_get_buffer( port->jack_port, nframes )
        );

    } else if( port->type == Audio::TYPE_EVENT && port->flow == Audio::FLOW_INPUT ) {

        lv2_evbuf_reset(port->evbuf, true);

        /* Write transport change event if applicable */
        LV2_Evbuf_Iterator iter = lv2_evbuf_begin(port->evbuf);

        if( xport_changed ) {
            lv2_evbuf_write(
                &iter, 0, 0,
                lv2_pos->type, lv2_pos->size, (uint8_t*) LV2_ATOM_BODY(lv2_pos)
            );
        }

        if( _request_update ) {

            /* Plugin state has changed, request an update */

            const LV2_Atom_Object get = {
                { sizeof(LV2_Atom_Object_Body), atom_Object },
                { 0, patch_Get }
            };

            lv2_evbuf_write(
                &iter, 0, 0,
                get.atom.type, get.atom.size, (uint8_t*) LV2_ATOM_BODY(&get)
            );

        }

        if( port->jack_port ) {

            /* Write Jack MIDI input */
            void* buf = jack_port_get_buffer(port->jack_port, nframes);

            for (uint32_t i = 0; i < jack_midi_get_event_count(buf); ++i) {

                jack_midi_event_t ev;
                jack_midi_event_get(&ev, buf, i);
                lv2_evbuf_write(&iter,
                    ev.time, 0,
                    midi_event_id,
                    ev.size, ev.buffer
                );

            }

        }

    } else if (port->type == Audio::TYPE_EVENT) {
        /* Clear event output for plugin to write to */
        lv2_evbuf_reset(port->evbuf, false);
    }

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


/**
 * Map of URI ID getting
 */

LV2_URID Plugin::mapURI( LV2_URID_Map_Handle handle, const char * uri ) {

    Plugin * jalv = (Plugin*) handle;

    zix_sem_wait(&jalv->symap_lock);

    const LV2_URID id = symap_map(jalv->_symap, uri);

    zix_sem_post(&jalv->symap_lock);

    return id;

};

const char * Plugin::unmapURI( LV2_URID_Map_Handle handle, LV2_URID urid ) {

	Plugin* plugin = (Plugin*)handle;
	zix_sem_wait(&plugin->symap_lock);
	const char * uri = symap_unmap( plugin->_symap, urid );
    zix_sem_post(&plugin->symap_lock);
	return uri;

};


/**
 *  Map function for URI map extension.
 */

uint32_t Plugin::uriToId( LV2_URI_Map_Callback_Data callback_data, const char * map, const char * uri ) {

    Plugin* plugin = (Plugin*)callback_data;
    zix_sem_wait(&plugin->symap_lock);
    const LV2_URID id = symap_map(plugin->_symap, uri);
    zix_sem_post(&plugin->symap_lock);

    return id;

};


/**
 * LV2 make path feature
 */

const char * Plugin::TEMP_PATH = "/tmp/";

char * Plugin::LV2MakePath( LV2_State_Make_Path_Handle handle, const char * path ) {

    Plugin * p = (Plugin*) handle;

	const size_t a_len = strlen( path );
	const size_t b_len = strlen( Plugin::TEMP_PATH );
	char * const fullPath = (char*)malloc(a_len + b_len + 1);

	memcpy(fullPath, path, a_len);
	memcpy(fullPath + a_len, Plugin::TEMP_PATH, b_len);
	fullPath[a_len + b_len] = '\0';

    return fullPath;

};

};
