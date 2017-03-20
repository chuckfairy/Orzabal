/**
 * Preset action item
 */
#pragma once

#include "PresetAction.h"

namespace LV2 {

/**
 * Main construct and setup
 */

PresetAction( QObject * parent, UI *, LilvNode * );
    QAction(parent),
    _jalv(jalv),
    _preset(preset)
{
    connect(
        this,
        SIGNAL(triggered()),
        this,
        SLOT(presetChosen())
    );
}


};
