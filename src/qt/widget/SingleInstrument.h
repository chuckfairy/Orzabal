/**
 * Single instrument widget
 */
#pragma once

#include <vector>

#include <QtCore>
#include <QWidget>

#include <ui_SingleInstrument.h>

#include "InstrumentDropdown.h"


using std::vector;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Widget {


/**
 * Main class
 */

class SingleInstrument : public QWidget {

    Q_OBJECT;

    public:

        SingleInstrument( MainWindow * );


        /**
         * Add action
         */

        void clearPlugin();

        void setPlugin( Audio::Plugin * );

        void handleChange( void * );


        /**
         * Getters
         */

        QWidget * getWidgetContainer() {

            return _WidgetContent;

        };


    private:

        MainWindow * _App;

        QWidget * _WidgetContent;

        InstrumentDropdown * _Dropdown;

        Ui_SingleInstrument _UI;

        QWidget * _LayoutWidget;

        bool HAS_PLUGIN;


        /**
         * Private methods
         */

        void setEvents();

};

}; }; };
