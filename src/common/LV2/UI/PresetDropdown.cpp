/**
 * Preset action item
 */
#pragma once

#include "PresetAction.h"
#include <Plugin.h>

namespace LV2 {

/**
 * Main construct and setup
 */

PresetDropdown::PresetDropdown( Plugin * p ) :
    _Plugin( p )
{
};

PresetDropdown::handleSelectionChanged( int index ) {

    //_Plugin->getPreset()->apply

};

};
