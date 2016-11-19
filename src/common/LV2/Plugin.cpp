/**
 * LV2 Plugin
 *
 */
#include <Audio/Port.h>

#include <string.h>

#include <lilv/lilv.h>

#include "LV2Plugin.h"

LV2Plugin::LV2Plugin() {


};


/**
 * Set ports from lilv plugin
 * loops thru ports
 *
 */

void LV2Plugin::setPorts() {

    long i;

    _portsNum

    numPorts = lilv_plugin_get_num_ports( _lilvPlugin );

    for( i = 0; i < _descriptor->PortCount; i++ ) {

        Port port = createPort( i );

        setPort( i, port );

    }

};


/**
 * Create lv2 port num
 *
 */

Port LV2Plugin::createPort( long portNum ) {

//    const LilvPort * port = lilv_plugin_get_port_by_index( _lilvPlugin, portNum );
//
//    const LilvPlugin* p = lilv_plugins_get(list, i);
//
//    LilvNode* n = lilv_plugin_get_name(p);
//    printf("%s\n", lilv_node_as_string(n));
//    lilv_node_free(n);

    //init struct

    return Port portReturn {};

};
