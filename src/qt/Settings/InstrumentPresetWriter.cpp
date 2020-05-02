/**
 * Layout writer qt ext
 */
#include "InstrumentPresetWriter.h"

using std::string;
using std::vector;
using nlohmann::json;
using Audio::Patchbay;



namespace Orza { namespace Settings {


InstrumentPresetWriter::InstrumentPresetWriter()
{
};

void InstrumentPresetWriter::writeLayoutToFile( string fileName, Patchbay * p ) {

	json output = getPatchbayJSON( fileName, p );

	saveToFile( fileName.c_str(), output );

};

}; };
