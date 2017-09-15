/**
 * Main window class
 *
 */
#pragma once

#include <QtCore>
#include <Qt>
#include <Jack/Server.h>
#include <PluginSearch/LoadedPlugins.h>

#include "ui_MainWindow.h"

#include "Config/BuildType.h"

#include "widget/InstrumentDropdown.h"
#include "widget/EffectsList.h"
#include "widget/SimpleLayout.h"

#include "Settings/MidiDeviceDropdown.h"


/**
 * Forwarding
 */
namespace Orza {

    namespace App { namespace Pi {

        class Layout;

    } }

    namespace App {  namespace Settings {

        class Layout;

    }; };

};


using namespace Orza::App;
using Orza::App::Settings::Layout;

using Orza::PluginSearch::LoadedPlugins;


/**
 * Main class
 */

class MainWindow : public QMainWindow {

    Q_OBJECT;

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


        /**
         * Layout @TODO use better base
         */

        SimpleLayout * getLayout();


        /**
         * Plugin search getter
         */

        LoadedPlugins * getPluginSearch();


        /**
         * Qt UI
         */

        Ui_MainWindow * getUI() {

            return &UI;

        };


        /**
         * Window actions
         */

        void goFullscreen();

        void goWindowed();


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
         * Plugin search
         */

        LoadedPlugins _PluginSearch;


        /**
         * Settings layout
         */

        Layout * _SettingsLayout;


        /**
         * Layout future layouter
         */

        SimpleLayout * _Layout;


        /**
         * Pi module
         */

        Orza::App::Pi::Layout * _Pi;


        /**
         * Orza build config
         */

        const Config::BuildType BUILD_TYPE = Config::ORZA_BUILD_CONFIG;

};
