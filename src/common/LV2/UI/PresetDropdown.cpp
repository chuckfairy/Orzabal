/**
 * Preset action item
 */
#include "PresetDropdown.h"
#include <LV2/Plugin.h>

namespace LV2 {

/**
 * Main construct and setup
 */

PresetDropdown::PresetDropdown( Plugin * p ) :
    _Plugin( p )
{
};

void PresetDropdown::handleSelectionChanged( int index ) {

    //_Plugin->getPreset()->apply

};

};
