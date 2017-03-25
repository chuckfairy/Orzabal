/**
 * Preset action item
 */
#pragma once

#include <QtCore>
#include <QComboBox>

#include <lilv/lilv.h>

#include <LV2/Preset.h>


namespace LV2 {


/**
 * Forwarding
 */

class Plugin;


/**
 * Main class
 */

class PresetDropdown : public QComboBox {

    Q_OBJECT

    private:

        Plugin * _Plugin;
        LilvNode * _preset;

        bool _LOADED = false;


    public:

        PresetDropdown( QWidget * parent );
        PresetDropdown( Plugin * plugin );


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

};
