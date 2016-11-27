/**
 * LV2 Plugin
 *
 */
#include <Audio/Port.h>

#include <string.h>

#include <lilv/lilv.h>

#include <lilv/lilv.h>

#include "Plugin.h"

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

        Port port = createPort( i );

        //setPort( i, port );

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

    setName( nodeName );

    lilv_node_free( n );

};


/**
 * Create lv2 port num
 *
 */

Port LV2Plugin::createPort( int long portNum ) {

    //    const LilvPort * port = lilv_plugin_get_port_by_index( _lilvPlugin, portNum );
    //
    //    const LilvPlugin* p = lilv_plugins_get(list, i);
    //
    //    LilvNode* n = lilv_plugin_get_name(p);
    //    printf("%s\n", lilv_node_as_string(n));
    //    lilv_node_free(n);

    //init struct

    Port portReturn;
    return portReturn;

};
