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
using Orza::Widget::SingleInstrument;


namespace Orza { namespace Settings {


InstrumentPresetLoader::InstrumentPresetLoader(
	MainWindow * win,
	Jack::Server * server
) :
	Orza::Layouts::PresetLoader( server ),
	win( win )
{

	//@TODO better

	Orza::Layouts::Layout * defaultLayout;

	if( Config::DEFAULT_LAYOUT == (string)"InstrumentEffect" ) {

		defaultLayout = new InstrumentEffect( win, _SingleInstrument, _Patchbay);

	} else {

		defaultLayout = new EffectLayout( win, _Patchbay );

	}

	win->getUI()->tab_instrument->layout()->addWidget(_SingleInstrument->getWidgetContainer());
	win->getUI()->tab_effects->layout()->addWidget(_Patchbay->getWidgetContainer());

	defaultLayout->setup();

	_CurrentLayout = defaultLayout;

	//_Repo.add( defaultLayout );

}

void InstrumentPresetLoader::load( json j ) {

	Orza::Layouts::PresetLoader::load(j);

};

}; };
