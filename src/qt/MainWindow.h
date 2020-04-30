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

#include <Widget/InstrumentDropdown.h>
#include <Widget/EffectsList.h>

#include <Layouts/LayoutLoader.h>
#include <Layouts/LayoutWriter.h>

#include "Settings/MidiDeviceDropdown.h"

#include <liborza-qt/src/Settings/Layout.h>


/**
 * Forwarding
 */
namespace Orza {

#ifdef IS_PI
	namespace App { namespace Pi {

		class Layout;

	}; };
#endif

	namespace MidiControl {

		class ControlTab;

	};

};


using namespace Orza::App;
using Orza::Settings::Layout;

using Orza::PluginSearch::LoadedPlugins;

using Orza::Layouts::LayoutLoader;
using Orza::Layouts::LayoutWriter;

using Orza::MidiControl::ControlTab;


/**
 * Main class
 */

class MainWindow : public QMainWindow {

	Q_OBJECT;

	public:

		//	override the constructor

		//MainWindow(QWidget * parent = 0, ::Qt::WindowFlags flags = 0);

		explicit MainWindow(QApplication *, QWidget * parent = 0, ::Qt::WindowFlags flags = 0);


		/**
		 * Qt Window UI
		 */

		Ui_MainWindow UI;


		/**
		 * Getters
		 */

		Jack::Server * getServer();


		/**
		 * Plugin search getter
		 */

		LoadedPlugins * getPluginSearch();

		/**
		 * Settings layout
		 */

		Layout * getSettingsLayout();


		/**
		 * Layout loader getter
		 */

		LayoutLoader * getLayoutLoader();


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
		 * Control tab
		 */

		ControlTab * _ControlTab;


		/**
		 * Layout loader
		 */

		LayoutLoader * _LayoutLoader;


		/**
		 * Pi module
		 */

#ifdef IS_PI
		Orza::App::Pi::Layout * _Pi;
#endif


		/**
		 * Orza build config
		 */

		const Config::BuildType BUILD_TYPE = Config::ORZA_BUILD_CONFIG;

};
