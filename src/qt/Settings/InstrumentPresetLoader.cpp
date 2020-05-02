/**
 * Simple layout start
 */
#include <MainWindow.h>
#include <Config/Defaults.h>

#include <Layouts/Effect/EffectLayout.h>
#include <Layouts/InstrumentEffect/InstrumentEffect.h>

#include "InstrumentPresetLoader.h"


using std::vector;
using nlohmann::json;

using Orza::Layouts::EffectLayout;
using Orza::Layouts::InstrumentEffect;


namespace Orza { namespace Settings {


InstrumentPresetLoader::InstrumentPresetLoader( MainWindow * win,  Jack::Server * server ) :
	Orza::Layouts::PresetLoader( server ),
	win( win )
{

	//@TODO better

	Orza::Layouts::Layout * defaultLayout;

	if( Config::DEFAULT_LAYOUT == "InstrumentEffect" ) {

		defaultLayout = new InstrumentEffect( win );

	} else {

		defaultLayout = new EffectLayout( win );

	}

	defaultLayout->setup();

	_CurrentLayout = defaultLayout;

	//_Repo.add( defaultLayout );

}

void InstrumentPresetLoader::load( json j ) {

	Orza::Layouts::PresetLoader::load(j);

};

}; };
