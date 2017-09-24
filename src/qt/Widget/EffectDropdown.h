/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <map>

#include <QtCore>
#include <QComboBox>

#include "AbstractPluginDropdown.h"

#include <PluginSearch/LoadedPlugins.h>

using std::vector;
using std::map;

using Orza::PluginSearch::LoadedPlugins;


namespace Orza { namespace App { namespace Widget {


/**
 * Effect dropdown GUI
 *
 */
class EffectDropdown : public AbstractPluginDropdown {

    public:

        EffectDropdown( QWidget * parent );
        EffectDropdown( LoadedPlugins * );
        EffectDropdown();

        void setupUI();

        void update();

};

} } };
