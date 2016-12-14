/**
 * LV2 Plugin
 *
 */
#include <string.h>
#include <iostream>

#include <Audio/Port.h>

#include <lilv/lilv.h>

#include <lilv/lilv.h>

#include "Plugin.h"

using std::string;

typedef struct {
	char** uris;
	size_t n_uris;
} URITable;

static void
uri_table_init(URITable* table)
{
	table->uris   = NULL;
	table->n_uris = 0;
}

static void
uri_table_destroy(URITable* table)
{
	free(table->uris);
}

static LV2_URID
uri_table_map(LV2_URID_Map_Handle handle,
              const char*         uri)
{
	URITable* table = (URITable*)handle;
	for (size_t i = 0; i < table->n_uris; ++i) {
		if (!strcmp(table->uris[i], uri)) {
			return i + 1;
		}
	}

	const size_t len = strlen(uri);
	table->uris = (char**)realloc(table->uris, ++table->n_uris * sizeof(char*));
	table->uris[table->n_uris - 1] = (char*)malloc(len + 1);
	memcpy(table->uris[table->n_uris - 1], uri, len + 1);
	return table->n_uris;
}

static const char*
uri_table_unmap(LV2_URID_Map_Handle handle,
                LV2_URID            urid)
{
	URITable* table = (URITable*)handle;
	if (urid > 0 && urid <= table->n_uris) {
		return table->uris[urid - 1];
	}
	return NULL;
}


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

    const char * uri = lilv_node_as_uri( lilv_plugin_get_uri( p ) );

    strcpy( _lilvURI, uri );

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


/**
 * LilvURI startup
 */

void LV2Plugin::start() {

    std::cout << _lilvURI << "\n";

    int block_size = 512;

    float* const buf = (float*)calloc(512 * 2, sizeof(float));

	URITable uri_table;
    uri_table_init(&uri_table);

    static LilvNode* urid_map        = NULL;

    LV2_URID_Map       map           = { &uri_table, uri_table_map };
    LV2_Feature        map_feature   = { LV2_URID_MAP_URI, &map };
    LV2_URID_Unmap     unmap         = { &uri_table, uri_table_unmap };
    LV2_Feature        unmap_feature = { LV2_URID_UNMAP_URI, &unmap };
    const LV2_Feature* features[]    = { &map_feature, &unmap_feature, NULL };

	float* const in  = buf;
	float* const out = buf + block_size;
	if (!buf) {
		fprintf(stderr, "Out of memory\n");
		return;
	}

    //LilvNodes* required = lilv_plugin_get_required_features(_lilvPlugin);
	//LILV_FOREACH(nodes, i, required) {
		//const LilvNode* feature = lilv_nodes_get(required, i);
		//if (!lilv_node_equals(feature, urid_map)) {
			//fprintf(stderr, "<%s> requires feature <%s>, skipping\n",
					//_lilvURI, lilv_node_as_uri(feature));
			//free(buf);
			//return;
		//}
	//}

    LilvInstance* instance = lilv_plugin_instantiate( _lilvPlugin, 48000.0, features );

    if (!instance) {
        fprintf(stderr, "Failed to instantiate <%s>\n",
                lilv_node_as_uri(lilv_plugin_get_uri(_lilvPlugin)));
        free(buf);
    }

};
