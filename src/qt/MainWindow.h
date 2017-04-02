/**
 * Main window class
 *
 */
#pragma once

#include <QtCore>
#include <Qt>
#include <Jack/Server.h>

#include "ui_MainWindow.h"

#include "Config/BuildType.h"

#include "widget/InstrumentDropdown.h"
#include "widget/EffectsList.h"
#include "widget/SimpleLayout.h"

#include "Settings/MidiDeviceDropdown.h"


/**
 * Forwarding
 */
namespace Orza { namespace Qt {  namespace Settings {

class Layout;

}; }; };


using Orza::Qt::Settings::Layout;
using namespace Orza::App;


/**
 * Main class
 */

class MainWindow : public QMainWindow {

    private:

        /**
         * Main audio server
         *
         */

        Jack::Server * _Server;


        /**
         * Instrument dropdown
         *
         */

        InstrumentDropdown * dropdown;


        /**
         * Effect dropdown
         *
         */

        EffectsList *effects;


        /**
         * Midi keyboard device dropdown
         *
         */

        MidiDeviceDropdown *midiDevices;


        /**
         * Settings layout
         */

        Layout * _SettingsLayout;


        /**
         * Layout future layouter
         */

        SimpleLayout * _Layout;


        /**
         * Orza build config
         */

        const Config::BuildType BUILD_TYPE = Config::ORZA_BUILD_CONFIG;


    public:

        //  override the constructor

        MainWindow(QWidget * parent = 0, ::Qt::WindowFlags flags = 0);


        /**
         * Qt Window UI
         */

        Ui_MainWindow UI;


        /**
         * Getters
         */

        Jack::Server * getServer();

        Ui_MainWindow * getUI() {

            return &UI;

        };


        /**
         * Window actions
         */

        void goFullscreen();

        void goWindowed();

};
