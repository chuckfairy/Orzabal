/**
 * Simple layout start
 */
#pragma once

#include <json/json.hpp>

#include <Jack/Server.h>
#include <Settings/PresetLoader.h>
#include <Layouts/Layout.h>

using nlohmann::json;

/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace Settings {


class InstrumentPresetLoader : public Orza::Layouts::PresetLoader {

	public:

		InstrumentPresetLoader( MainWindow *, Jack::Server * );


		/**
		 * Virtuals
		 */

		void load( json settings );


	private:

		MainWindow * win;
		Orza::Layouts::Layout * _CurrentLayout;

};

}; };
