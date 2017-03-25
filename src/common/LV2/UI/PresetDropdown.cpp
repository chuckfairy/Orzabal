/**
 * Preset action item
 */
#include "PresetDropdown.h"

#include <LV2/Plugin.h>
#include <LV2/PluginPreset.h>

namespace LV2 {

/**
 * Main construct and setup
 */

PresetDropdown::PresetDropdown( Plugin * p ) :
    _Plugin( p )
{

    connect(
        this,
        SIGNAL( currentIndexChanged( int ) ),
        this,
        SLOT( handleSelectionChanged( int ) )
    );

};


/**
 * char
 */

void PresetDropdown::load() {

    PluginPreset * p = _Plugin->getPreset();
    vector<Audio::Preset*> presets = p->getAll();
    vector<Audio::Preset*>::const_iterator it;

    for( it = presets.begin(); it != presets.end(); ++ it ) {

        addItem( (*it)->name );

    }

    _LOADED = true;

};


/**
 * Dropdown change leads to preset
 * change right away
 *
 */

void PresetDropdown::handleSelectionChanged( int index ) {

    if( ! _LOADED ) { return; }

    std::cout << "CHANG DROPDOWn\n";

    _Plugin->getPreset()->applyPreset( (uint32_t) index );

};

};
