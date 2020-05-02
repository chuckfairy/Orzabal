/**
 * Layout writer qt ext
 */
#pragma once

#include <string>
#include <vector>

#include <json/json.hpp>

#include <Audio/Patchbay.h>
#include <Layouts/LayoutWriter.h>


using std::string;
using std::vector;
using nlohmann::json;
using Audio::Patchbay;



namespace Orza { namespace Settings {


class InstrumentPresetWriter : public Orza::Layouts::LayoutWriter {

	public:

		 InstrumentPresetWriter();
		 ~InstrumentPresetWriter() {};

		 /**
		  * @TODO
		  */
		void writeLayoutToFile( string fileName, Patchbay * p );

	private:

};

}; };
