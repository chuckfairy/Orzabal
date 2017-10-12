/**
 * Get all presets
 */
#include <iostream>
#include <stdexcept>

#include "Resource/World.h"
#include "Plugin.h"
#include "PluginPreset.h"
#include "PluginState.h"
#include "Preset.h"

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

    loadPresets();

};


/**
 * Lilv node setup
 */

void PluginPreset::setNodes() {

    LilvWorld * world = Resource::World::getResource();

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

void PluginPreset::loadPresets() {

    //Grab from lilv plugin

	LilvNodes * lilvPresets = lilv_plugin_get_related(
        _Plugin->getLilvPlugin(),
        _pset_Preset
    );

    LilvWorld * world = Resource::World::getResource();

	LILV_FOREACH( nodes, i, lilvPresets ) {

        Preset * audioPreset = new Preset;

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


        audioPreset->name = lilv_node_as_string( label );

        audioPreset->lilvPreset = preset;

        _presets.push_back( (Audio::Preset*) audioPreset );

        lilv_nodes_free( labels );

    }

    //@TODO move to delete
    //lilv_nodes_free( lilvPresets );

};


/**
 * Main preset state applys
 */


void PluginPreset::applyPreset() {

    _Plugin->getState()->setLilvState( _preset );

};

void PluginPreset::applyPreset( uint32_t index ) {

    applyPreset( _presets[ index ] );

};


void PluginPreset::applyPreset( Audio::Preset * p ) {

    setPreset( p );

    applyPreset();

};

};
