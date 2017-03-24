/**
 * Get all presets
 */
#include "Plugin.h"
#include "PluginPreset.h"

namespace LV2 {

/**
 * Main construct
 */

PluginPreset::PluginPreset( Plugin * plugin )
    : _Plugin( plugin )
{
};


/**
 * Setup impl
 */

void PluginPreset::setup() {

    setNodes();

};


/**
 * Lilv node setup
 */

void PluginPreset::setNodes() {

    LilvWorld * world = _Plugin->getLilvWorld();

    if( ! world ) {

        throw std::runtime_error(
            "Lilv world not start"
        );

    }

    _pset_Preset = lilv_new_uri( world, LV2_PRESETS__Preset );
    _rdfs_label = lilv_new_uri( world, LILV_NS_RDFS "label" );

};


/**
 * Get all plugin presets
 */

vector<Audio::Preset*> PluginPreset::getAll() {

    vector<Audio::Preset*> presets;


    //Grab from lilv plugin

	LilvNodes * lilvPresets = lilv_plugin_get_related(
        _Plugin->getLilvPlugin(),
        _pset_Preset
    );

    LilvWorld * world = _Plugin->getLilvWorld();

    std::cout << "PRESET SETTING";

	LILV_FOREACH( nodes, i, lilvPresets ) {


        //Grab needed nodes

		const LilvNode * preset = lilv_nodes_get( lilvPresets, i );

        lilv_world_load_resource( world, preset );

        LilvNodes * labels = lilv_world_find_nodes(
            world,
            preset,
            _rdfs_label,
            NULL
        );

        if( ! labels ) {

            //@TODO Log
            //lilv_node_as_string(lilv_nodes_get(presets, i)));
            continue;

        }


        //Create preset

        const LilvNode* label = lilv_nodes_get_first( labels );

        Audio::Preset * audioPreset = new Audio::Preset;

        audioPreset->name = lilv_node_as_string( label );

        presets.push_back( audioPreset );

        std::cout << audioPreset->name;

        lilv_nodes_free( labels );

    }

    lilv_nodes_free( lilvPresets );

    return presets;

};


/**
 * Main preset state applys
 */

void PluginPreset::applyPreset() {

};


void PluginPreset::applyPreset( Audio::Preset * p ) {

    setPreset( p );

    applyPreset();

};

};
