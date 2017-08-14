/**
 * Settings layout tab
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Layouts/LayoutWriter.h>

#include "OutputDropdown.h"


/**
 * Forwading
 */

class MainWindow;

namespace Orza { namespace App {  namespace Settings {

/**
 * class
 */

class Layout : public QWidget {

    Q_OBJECT;


    public:

        Layout( MainWindow * );

        void updateOutputPorts();

        /**
         * Save layout
         */

        void saveLayout();


    public slots:

        void handleSaveClick();


    private:

        MainWindow * _App;

        Orza::App::Layouts::LayoutWriter * _LayoutWriter;

        /**
         * Widget dropdowns
         */

        OutputDropdown * _LeftOutput;
        OutputDropdown * _RightOutput;


        /**
         * Main event
         */

        Util::Event * _Event;


        /**
         * Private setters for cleaniness
         */

        void setDropdowns();

        void setEvents();

        void setAppUI();

};

}; }; };
