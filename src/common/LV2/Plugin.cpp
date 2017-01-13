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

    atom_Object = symap_map(_symap, LV2_ATOM__Object);
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
    //

    _time_position = symap_map(_symap, LV2_TIME__Position);
    _time_bar = symap_map(_symap, LV2_TIME__bar);
    _time_barBeat = symap_map(_symap, LV2_TIME__barBeat);
    _time_beatUnit = symap_map(_symap, LV2_TIME__beatUnit);
    _time_beatsPerBar = symap_map(_symap, LV2_TIME__beatsPerBar);
    _time_beatsPerMinute  = symap_map(_symap, LV2_TIME__beatsPerMinute);
    _time_frame = symap_map(_symap, LV2_TIME__frame);
    _time_speed = symap_map(_symap, LV2_TIME__speed);

    LV2_URID ui_updateRate = symap_map(_symap, LV2_UI__updateRate);
    LilvNode * work_interface = lilv_new_uri( _Host->getLilvWorld(), LV2_WORKER__interface );
    LilvNode * work_schedule = lilv_new_uri( _Host->getLilvWorld(), LV2_WORKER__schedule );

    int block_length = _Host->getBufferSize();

    int midi_buf_size = _Host->getMidiBufferSize();

    sample_rate = _Host->getSampleRate();

    ui_update_hz = (float)sample_rate / midi_buf_size * 2.0f;


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

    zix_sem_wait(&exit_sem);

    //if( jalv.opts.controls ) {
        //for( char** c = jalv.opts.controls; *c; ++c ) {
            //jalv_apply_control_arg(&jalv, *c);
        //}
    //}
    /* Wait for finish signal from UI or signal handler */

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
 *
 */

void Plugin::updateJack( jack_nframes_t nframes ) {

	/* Get Jack transport position */

    jack_client_t * jackClient = _Host->getJackClient();

    jack_position_t pos;

    const bool rolling = (
        jack_transport_query( jackClient, &pos ) == JackTransportRolling
    );

    /* If transport state is not as expected, then something has changed */
    const bool xport_changed = (rolling != _transportRolling ||
            pos.frame != _position ||
            pos.beats_per_minute != _bpm);

    uint8_t   pos_buf[256];
    LV2_Atom* lv2_pos = (LV2_Atom*)pos_buf;

    if (xport_changed) {

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

    param_sampleRate = symap_map(_symap, LV2_PARAMETERS__sampleRate);
    LV2_URID patch_Get = symap_map(_symap, LV2_PATCH__Get);


    /* Prepare port buffers */

    for (uint32_t p = 0; p < _numPorts; ++p) {

        Port * port = (Port*) _ports[ p ];

        if( port->type == Audio::TYPE_AUDIO && port->jack_port ) {

            /* Connect plugin port directly to Jack port buffer */
            lilv_instance_connect_port(
                _lilvInstance,
                p,
                jack_port_get_buffer( port->jack_port, nframes )
            );

        } else if (port->type == Audio::TYPE_CV && port->jack_port) {

            /* Connect plugin port directly to Jack port buffer */
            lilv_instance_connect_port(
                    _lilvInstance, p,
                    jack_port_get_buffer( port->jack_port, nframes ) );

        } else if ( port->type == Audio::TYPE_EVENT && port->flow == Audio::FLOW_INPUT ) {

            lv2_evbuf_reset(port->evbuf, true);

            /* Write transport change event if applicable */
            LV2_Evbuf_Iterator iter = lv2_evbuf_begin(port->evbuf);
            if (xport_changed) {
                lv2_evbuf_write(
                    &iter, 0, 0,
                    lv2_pos->type, lv2_pos->size, LV2_ATOM_BODY(lv2_pos)
                );
            }

            if (_request_update) {

                /* Plugin state has changed, request an update */

                const LV2_Atom_Object get = {
                    { sizeof(LV2_Atom_Object_Body), atom_Object },
                    { 0, patch_Get } };

                lv2_evbuf_write(
                    &iter, 0, 0,
                    get.atom.type, get.atom.size, LV2_ATOM_BODY(&get)
                );

            }

            if (port->jack_port) {

                /* Write Jack MIDI input */
                void* buf = jack_port_get_buffer(port->jack_port, nframes);
                for (uint32_t i = 0; i < jack_midi_get_event_count(buf); ++i) {
                    jack_midi_event_t ev;
                    jack_midi_event_get(&ev, buf, i);
                    lv2_evbuf_write(&iter,
                            ev.time, 0,
                            jalv->midi_event_id,
                            ev.size, ev.buffer);
                }

            }
        } else if (port->type == Audio::TYPE_EVENT) {
            /* Clear event output for plugin to write to */
            lv2_evbuf_reset(port->evbuf, false);
        }

    }

    _request_update = false;


    /* Read and apply control change events from UI */

    if( _UI ) {

//        ControlChange ev;
//        const size_t space = jack_ringbuffer_read_space(jalv->ui_events);
//
//        for (size_t i = 0; i < space; i += sizeof(ev) + ev.size) {
//
//            jack_ringbuffer_read(jalv->ui_events, (char*)&ev, sizeof(ev));
//            char body[ev.size];
//
//            if (jack_ringbuffer_read(jalv->ui_events, body, ev.size) != ev.size) {
//                fprintf(stderr, "error: Error reading from UI ring buffer\n");
//                break;
//            }
//
//            //assert(ev.index < jalv->num_ports);
//
//            Port * port = _ports[ev.index];
//
//            if (ev.protocol == 0) {
//                assert(ev.size == sizeof(float));
//                port->control = *(float*)body;
//            } else if (ev.protocol == jalv->urids.atom_eventTransfer) {
//                LV2_Evbuf_Iterator    e    = lv2_evbuf_end(port->evbuf);
//                const LV2_Atom* const atom = (const LV2_Atom*)body;
//                lv2_evbuf_write(&e, nframes, 0, atom->type, atom->size,
//                        LV2_ATOM_BODY_CONST(atom));
//            } else {
//                fprintf(stderr, "error: Unknown control change protocol %d\n",
//                        ev.protocol);
//            }
//
//        }


    }

    /* Run plugin for this cycle */
    lilv_instance_run(_lilvInstance, nframes);

    /* Process any worker replies. */
    jalv_worker_emit_responses(&jalv->state_worker, _lilvInstance);
    jalv_worker_emit_responses(&jalv->worker, _lilvInstance);

    /* Notify the plugin the run() cycle is finished */
    if (jalv->worker.iface && jalv->worker.iface->end_run) {
        jalv->worker.iface->end_run(_lilvInstance->lv2_handle);
    }

    /* Check if it's time to send updates to the UI */
    jalv->event_delta_t += nframes;
    bool send_ui_updates = false;
    jack_nframes_t update_frames = sample_rate / ui_update_hz;

    if (jalv->has_ui && (jalv->event_delta_t > update_frames)) {
        send_ui_updates = true;
        jalv->event_delta_t = 0;
    }

    /* Deliver MIDI output and UI events */
    for (uint32_t p = 0; p < _numPorts; ++p) {
        struct Port* const port = &jalv->ports[p];
        if (port->flow == Audio::FLOW_OUTPUT && port->type == Audio::TYPE_CONTROL &&
                lilv_port_has_property( _lilvPlugin, port->lilv_port,
                    jalv->nodes.lv2_reportsLatency)) {
            if (jalv->plugin_latency != port->control) {
                jalv->plugin_latency = port->control;
                jack_recompute_total_latencies(jalv->jack_client);
            }
        }

        if (port->flow == Audio::FLOW_OUTPUT && port->type == Audio::TYPE_EVENT) {
            void* buf = NULL;
            if (port->jack_port) {
                buf = jack_port_get_buffer(port->jack_port, nframes);
                jack_midi_clear_buffer(buf);
            }

            for (LV2_Evbuf_Iterator i = lv2_evbuf_begin(port->evbuf);
                    lv2_evbuf_is_valid(i);
                    i = lv2_evbuf_next(i)) {
                uint32_t frames, subframes, type, size;
                uint8_t* body;
                lv2_evbuf_get(i, &frames, &subframes, &type, &size, &body);
                if (buf && type == jalv->midi_event_id) {
                    jack_midi_event_write(buf, frames, body, size);
                }

                /* TODO: Be more disciminate about what to send */
                if (jalv->has_ui && !port->old_api) {
                    char evbuf[sizeof(ControlChange) + sizeof(LV2_Atom)];
                    ControlChange* ev = (ControlChange*)evbuf;
                    ev->index    = p;
                    ev->protocol = jalv->urids.atom_eventTransfer;
                    ev->size     = sizeof(LV2_Atom) + size;
                    LV2_Atom* atom = (LV2_Atom*)ev->body;
                    atom->type = type;
                    atom->size = size;
                    if (jack_ringbuffer_write_space(jalv->plugin_events)
                            < sizeof(evbuf) + size) {
                        fprintf(stderr, "Plugin => UI buffer overflow!\n");
                        break;
                    }
                    jack_ringbuffer_write(jalv->plugin_events, evbuf, sizeof(evbuf));
                    /* TODO: race, ensure reader handles this correctly */
                    jack_ringbuffer_write(jalv->plugin_events, (void*)body, size);
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
            if (jack_ringbuffer_write(jalv->plugin_events, buf, sizeof(buf))
                    < sizeof(buf)) {
                fprintf(stderr, "Plugin => UI buffer overflow!\n");
            }
        }
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

};
