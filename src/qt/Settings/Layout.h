/**
 * Settings layout tab
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Layouts/LayoutWriter.h>

#include <Widget/OutputDropdown.h>
#include <Widget/InputDropdown.h>
#include <Widget/BaseLineEdit.h>

using Orza::App::Widget::InputDropdown;
using Orza::App::Widget::OutputDropdown;

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
         * Save preset layout
         */

        void saveLayout();

        void loadPreset();

        InputDropdown * getInputDropdown() {

            return _InputDropdown;

        };


        /**
         * Input change handle
         */

        void handleInputChange( void * data );


    public slots:

        void handleSaveClick();

        void handlePresetLoadClick();


    private:

        MainWindow * _App;

        Orza::App::Layouts::LayoutWriter * _LayoutWriter;

        /**
         * Widget dropdowns
         */

        OutputDropdown * _LeftOutput;
        OutputDropdown * _RightOutput;

        InputDropdown * _InputDropdown;

        Widget::BaseLineEdit * _PresetName;


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
