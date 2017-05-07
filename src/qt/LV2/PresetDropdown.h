/**
 * Preset action item
 */
#pragma once

#include <QtCore>
#include <QComboBox>

#include <lilv/lilv.h>

#include <LV2/Preset.h>


/**
 * Forwarding
 */

namespace LV2 {

class Plugin;

};


namespace Orza { namespace App { namespace LV2UI {


/**
 * Main class
 */

class PresetDropdown : public QComboBox {

    Q_OBJECT

    private:

        LV2::Plugin * _Plugin;
        LilvNode * _preset;

        bool _LOADED = false;


    public:

        PresetDropdown( QWidget * parent );
        PresetDropdown( LV2::Plugin * plugin );


        /**
         * Main loader
         */

        void load();


    public slots:


        /**
         * Change event
         *
         */

        void handleSelectionChanged( int index );

};

}; }; };
