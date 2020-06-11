/**
 * Simple layout start
 */
#include <string.h>

#include <json/json.hpp>

#include "InstrumentEffect.h"

#include <Audio/UI.h>

#include <MainWindow.h>


using nlohmann::json;

using Orza::Widget::SingleInstrument;


namespace Orza { namespace Layouts {

/**
 * Construct
 */

InstrumentEffect::InstrumentEffect( MainWindow * app ) :
	_App( app ),
	_SingleInstrument( new SingleInstrument( app->getServer() ) ),
	_Patchbay( new Orza::Widget::Patchbay( app->getServer() ) )
{
};

InstrumentEffect::InstrumentEffect(
		MainWindow * app,
		SingleInstrument * inst,
		Orza::Widget::Patchbay * patch
	) :
	_App( app ),
	_SingleInstrument( inst ),
	_Patchbay( patch )
{
};


/**
 * Main virtuals
 */

void InstrumentEffect::setup() {

	//Patchbay setup

	_App->getUI()
		->tabWidget->widget(0)->show();

	_App->getUI()
		->tabWidget->widget(1)->show();

	_App->getUI()->tabWidget->setCurrentIndex( 0 );

};


void InstrumentEffect::takedown() {

	_App->getUI()
		->tabWidget->widget(0)->hide();

	_App->getUI()
		->tabWidget->widget(1)->hide();

};

/**
 * Main layout load
 */

void InstrumentEffect::load( json j ) {

	Audio::Patchbay * host = _App->getServer()->getPatchbay();

	host->setActive( false );


	if( ! j["instruments"].empty() ) {

		json instrument = j["instruments" ][ 0 ];

		std::string id = instrument["id"];

		Audio::Plugin * p = _App->getPluginSearch()->getById( id.c_str() );
		Audio::Plugin * clone = (Audio::Plugin*) p->clone();

		_SingleInstrument->setPlugin( clone );

		setPortsFromJSON( clone, instrument );

		clone->getUI()->updateDrivers();

	}



	// Plugin effects

	_Patchbay->clearPlugins();

	if( ! j["effects"].empty() ) {

		for( json::iterator it = j["effects"].begin(); it != j["effects"].end(); ++it ) {

			json effect = *it;

			std::string id = effect["id"];

			Audio::Plugin * plug = _App->getPluginSearch()->getById( id.c_str() );

			Audio::Plugin * p = plug->clone();

			_Patchbay->addPlugin( p );

			setPortsFromJSON( p, effect );

			p->getUI()->updateDrivers();

		}

	}

	host->setActive( true );

};

}; };
