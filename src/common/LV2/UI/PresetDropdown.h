/**
 * Preset action item
 */
#pragma once

#include <QtCore>
#include <QComboBox>

#include <lilv/lilv.h>

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

    public:

        PresetDropdown( QWidget * parent );
        PresetDropdown( Plugin * plugin );


    public slots:


        /**
         * Change event
         *
         */

        void handleSelectionChanged( int index );

};

};
