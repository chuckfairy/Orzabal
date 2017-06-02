/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <map>

#include <QtCore>
#include <QComboBox>

#include "AbstractPluginDropdown.h"

using std::map;


namespace Orza { namespace App { namespace Widget {


/**
 * Effect dropdown GUI
 *
 */
class EffectDropdown : public AbstractPluginDropdown {

    public:

        EffectDropdown( QWidget * parent );
        EffectDropdown( Jack::Server * );
        EffectDropdown();

        void setupUI();

        void update();

};

} } };
