/**
 * Preset action item
 */
#pragma once

#include <QtCore>
#include <QComboBox>

namespace LV2 {

/**
 * Forwarding
 */

class Plugin;


/**
 * Main class
 */

class PresetDropdown : public QCombobox {

    Q_OBJECT

    private:

        Plugin * _Plugin;
        LilvNode * _preset;

    public:

        PresetDropdown( Plugin * plugin ) :
            _Plugin(plugin)
        {
        }


    public slots:


        /**
         * Change event
         *
         */

        void handleSelectionChanged( int index );

};

};
