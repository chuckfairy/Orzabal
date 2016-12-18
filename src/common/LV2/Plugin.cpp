/**
 * LV2 Plugin
 *
 */
#include <string.h>
#include <iostream>

//#include <Audio/Port.h>

#include <lilv/lilv.h>

#include <jack/jack.h>

#include "Plugin.h"
#include "Port.h"

using std::string;


/**
 * default
 *
 */

LV2Plugin::LV2Plugin() {};


/**
 * Lilv plugin instance place
 */

LV2Plugin::LV2Plugin( const LilvPlugin* p ) {

    setLilvPlugin( p );

};


/**
 * Set ports from lilv plugin
 * loops thru ports
 *
 */

void LV2Plugin::setPorts() {

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

void LV2Plugin::setLilvPlugin( const LilvPlugin * p ) {

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

Audio::Port LV2Plugin::createPort( int long portNum ) {

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

void LV2Plugin::start() {

    std::cout << _lilvURI << "\n";

    int block_size = 512;

	/* Build options array to pass to plugin */

	//const LV2_Options_Option options[] = {
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.param_sampleRate,
		  //sizeof(float), jalv.urids.atom_Float, &jalv.sample_rate },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_minBlockLength,
		  //sizeof(int32_t), jalv.urids.atom_Int, &jalv.block_length },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_maxBlockLength,
		  //sizeof(int32_t), jalv.urids.atom_Int, &jalv.block_length },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_sequenceSize,
		  //sizeof(int32_t), jalv.urids.atom_Int, &jalv.midi_buf_size },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.ui_updateRate,
		  //sizeof(float), jalv.urids.atom_Float, &jalv.ui_update_hz },
		//{ LV2_OPTIONS_INSTANCE, 0, 0, 0, 0, NULL }

	//};

     //Instantiate the plugin 
	//jalv.instance = lilv_plugin_instantiate(
		//jalv.plugin, jalv.sample_rate, features);

};
