/**
 * LV2 Plugin
 *
 */
#include <string.h>
#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//#include <Audio/Port.h>

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/data-access/data-access.h>
#include <lv2/lv2plug.in/ns/ext/event/event.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/parameters/parameters.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>
#include <lv2/lv2plug.in/ns/ext/port-groups/port-groups.h>
#include <lv2/lv2plug.in/ns/ext/port-props/port-props.h>
#include <lv2/lv2plug.in/ns/ext/presets/presets.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

#include <lilv/lilv.h>

#include <jack/jack.h>

#include "include/symap.h"
#include "Plugin.h"
#include "Port.h"

using std::string;


namespace LV2 {


/**
 * Lilv plugin instance place
 */

Plugin::Plugin( const LilvPlugin* p, LilvWorld * w ) {

    setLilvPlugin( p );

    setLilvWorld( w );

};


/**
 * Set ports from lilv plugin
 * loops thru ports
 *
 */

void Plugin::setPorts() {

    long i;

    int long numPorts = lilv_plugin_get_num_ports( _lilvPlugin );

    for( int long i = 0; i < numPorts; i++ ) {

        Audio::Port port = createPort( i );

        //setAudio::Port( i, port );

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

};


/**
 * Create lv2 port num
 *
 */

Audio::Port Plugin::createPort( int long portNum ) {

    //    const LilvAudio::Port * port = lilv_plugin_get_port_by_index( _lilvPlugin, portNum );
    //
    //    const LilvPlugin* p = lilv_plugins_get(list, i);
    //
    //    LilvNode* n = lilv_plugin_get_name(p);
    //    printf("%s\n", lilv_node_as_string(n));
    //    lilv_node_free(n);

    //init struct

	//struct LV2::Port* const port = &_ports[portNum];

//	const LilvNode* sym = lilv_port_get_symbol(_lilvPlugin, port->lilv_port);
//
//	/* Connect unsupported ports to NULL (known to be optional by this point) */
//	if (port->flow == FLOW_UNKNOWN || port->type == TYPE_UNKNOWN) {
//		lilv_instance_connect_port(jalv->instance, port_index, NULL);
//		return;
//	}
//
//	/* Build Jack flags for port */
//	enum JackAudio::PortFlags jack_flags = (port->flow == FLOW_INPUT)
//		? JackAudio::PortIsInput
//		: JackAudio::PortIsOutput;
//
//	/* Connect the port based on its type */
//	switch (port->type) {
//	case TYPE_CONTROL:
//		print_control_value(jalv, port, port->control);
//		lilv_instance_connect_port(jalv->instance, port_index, &port->control);
//		break;
//	case TYPE_AUDIO:
//		port->jack_port = jack_port_register(
//			jalv->jack_client, lilv_node_as_string(sym),
//			JACK_DEFAULT_AUDIO_TYPE, jack_flags, 0);
//		break;
//#ifdef HAVE_JACK_METADATA
//	case TYPE_CV:
//		port->jack_port = jack_port_register(
//			jalv->jack_client, lilv_node_as_string(sym),
//			JACK_DEFAULT_AUDIO_TYPE, jack_flags, 0);
//		if (port->jack_port) {
//			jack_set_property(jalv->jack_client, jack_port_uuid(port->jack_port),
//			                  "http://jackaudio.org/metadata/signal-type", "CV",
//			                  "text/plain");
//		}
//		break;
//#endif
//	case TYPE_EVENT:
//		if (lilv_port_supports_event(
//			    jalv->plugin, port->lilv_port, jalv->nodes.midi_MidiEvent)) {
//			port->jack_port = jack_port_register(
//				jalv->jack_client, lilv_node_as_string(sym),
//				JACK_DEFAULT_MIDI_TYPE, jack_flags, 0);
//		}
//		break;
//	default:
//		break;
//	}
//
//#ifdef HAVE_JACK_METADATA
//	if (port->jack_port) {
//		// Set port order to index
//		char index_str[16];
//		snprintf(index_str, sizeof(index_str), "%d", port_index);
//		jack_set_property(jalv->jack_client, jack_port_uuid(port->jack_port),
//		                  "http://jackaudio.org/metadata/order", index_str,
//		                  "http://www.w3.org/2001/XMLSchema#integer");
//
//		// Set port pretty name to label
//		LilvNode* name = lilv_port_get_name(jalv->plugin, port->lilv_port);
//		jack_set_property(jalv->jack_client, jack_port_uuid(port->jack_port),
//		                  JACK_METADATA_PRETTY_NAME, lilv_node_as_string(name),
//		                  "text/plain");
//		lilv_node_free(name);
//	}
//#endif

    Audio::Port portReturn;
    return portReturn;

};


/**
 * LilvURI startup
 */

void Plugin::start() {

    std::cout << _lilvURI << "\n";

    int block_size = 512;

	/* Build options array to pass to plugin */

	int uiUpdateHZ = 60;
	int buffer_size = 4096;

    int symap;

    int param_sampleRate = symap_map(symap, LV2_PARAMETERS__sampleRate);

	/* Build options array to pass to plugin */
	const LV2_Options_Option options[] = {
		{
            LV2_OPTIONS_INSTANCE, 0, jalv.urids.param_sampleRate,
            sizeof(float), jalv.urids.atom_Float, &jalv.sample_rate
        },
		{
            LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_minBlockLength,
            sizeof(int32_t), jalv.urids.atom_Int, &jalv.block_length
        },
		{
            LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_maxBlockLength,
            sizeof(int32_t), jalv.urids.atom_Int, &jalv.block_length
        },
		{
            LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_sequenceSize,
            sizeof(int32_t), jalv.urids.atom_Int, &jalv.midi_buf_size
        },
		{
            LV2_OPTIONS_INSTANCE, 0, jalv.urids.ui_updateRate,
            sizeof(float), jalv.urids.atom_Float, &jalv.ui_update_hz
        },
		{ LV2_OPTIONS_INSTANCE, 0, 0, 0, 0, NULL }
	};

	/* Instantiate the plugin */
	_lilvInstance = lilv_plugin_instantiate( jalv.plugin, jalv.sample_rate, features);
	if (!jalv.instance) {
		die("Failed to instantiate plugin.\n");
	}

	ext_data.data_access = lilv_instance_get_descriptor(jalv.instance)->extension_data;

	fprintf(stderr, "\n");
	if (!jalv.buf_size_set) {
		jalv_allocate_port_buffers(&jalv);
	}

	/* Create workers if necessary */
	if (lilv_plugin_has_feature(jalv.plugin, jalv.nodes.work_schedule)
	    && lilv_plugin_has_extension_data(jalv.plugin, jalv.nodes.work_interface)) {
		const LV2_Worker_Interface* iface = (const LV2_Worker_Interface*)
			lilv_instance_get_extension_data(jalv.instance, LV2_WORKER__interface);

		jalv_worker_init(&jalv, &jalv.worker, iface, true);
		if (jalv.safe_restore) {
			jalv_worker_init(&jalv, &jalv.state_worker, iface, false);
		}
	}

	/* Apply loaded state to plugin instance if necessary */
	if (state) {
		jalv_apply_state(&jalv, state);
	}

	if (jalv.opts.controls) {
		for (char** c = jalv.opts.controls; *c; ++c) {
			jalv_apply_control_arg(&jalv, *c);
		}
	}

	/* Set Jack callbacks */
	jack_set_process_callback(jalv.jack_client,
	                          &jack_process_cb, (void*)(&jalv));
	jack_set_buffer_size_callback(jalv.jack_client,
	                              &jack_buffer_size_cb, (void*)(&jalv));
	jack_on_shutdown(jalv.jack_client,
	                 &jack_shutdown_cb, (void*)(&jalv));
	jack_set_latency_callback(jalv.jack_client,
	                          &jack_latency_cb, (void*)(&jalv));
#ifdef JALV_JACK_SESSION
	jack_set_session_callback(jalv.jack_client,
	                          &jack_session_cb, (void*)(&jalv));
#endif

	/* Create Jack ports and connect plugin ports to buffers */
	for (uint32_t i = 0; i < jalv.num_ports; ++i) {
		activate_port(&jalv, i);
	}

	/* Activate plugin */
	lilv_instance_activate(jalv.instance);

	/* Activate Jack */
	jack_activate(jalv.jack_client);
	jalv.sample_rate = jack_get_sample_rate(jalv.jack_client);
	jalv.play_state  = JALV_RUNNING;

	/* Run UI (or prompt at console) */
	jalv_open_ui(&jalv);

	/* Wait for finish signal from UI or signal handler */
	zix_sem_wait(&exit_sem);
	jalv.exit = true;

	fprintf(stderr, "Exiting...\n");

	/* Terminate the worker */
	jalv_worker_finish(&jalv.worker);

	/* Deactivate JACK */
	jack_deactivate(jalv.jack_client);
	for (uint32_t i = 0; i < jalv.num_ports; ++i) {
		if (jalv.ports[i].evbuf) {
			lv2_evbuf_free(jalv.ports[i].evbuf);
		}
	}
	jack_client_close(jalv.jack_client);

	/* Deactivate plugin */
	suil_instance_free(jalv.ui_instance);
	lilv_instance_deactivate(jalv.instance);
	lilv_instance_free(jalv.instance);

	/* Clean up */
	free(jalv.ports);
	jack_ringbuffer_free(jalv.ui_events);
	jack_ringbuffer_free(jalv.plugin_events);
	for (LilvNode** n = (LilvNode**)&jalv.nodes; *n; ++n) {
		lilv_node_free(*n);
	}
	symap_free(jalv.symap);
	zix_sem_destroy(&jalv.symap_lock);
	suil_host_free(jalv.ui_host);
	sratom_free(jalv.sratom);
	sratom_free(jalv.ui_sratom);
	lilv_uis_free(jalv.uis);
	lilv_world_free(world);

	zix_sem_destroy(&exit_sem);

	remove(jalv.temp_dir);
	free(jalv.temp_dir);
	free(jalv.ui_event_buf);

};

};
