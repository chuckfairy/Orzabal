/**
 * Effect layout impl
 */
#include <MainWindow.h>

#include "EffectLayout.h"

#include <Jack/PatchbayEffects.h>
#include <Settings/Layout.h>

#include <Audio/UI.h>

using nlohmann::json;


namespace Orza { namespace Layouts {


/**
 * Construct
 */

EffectLayout::EffectLayout( MainWindow * app ) :
	_App( app ),
	_Patchbay( new Orza::Widget::Patchbay( app->getServer() ) )
{

	_name = "effect";

};

EffectLayout::EffectLayout( MainWindow * app, Orza::Widget::Patchbay * patch ) :
	_App( app ),
	_Patchbay( patch )
{

	_name = "effect";

};


/**
 * Main setup
 */

void EffectLayout::setup() {

	_App->getUI()
		->tabWidget->removeTab(0);

	//_App->getUI()
		//->tabWidget->widget(1)->show();

	_App->getUI()->tabWidget->setCurrentIndex( 0 );


	//Connect default first input

	vector<Jack::Port> outputs = _App->getServer()->getAudio()->getOutputPorts();

	if( ! outputs.empty() ) {

		_App->getServer()
			->getPatchbay()
			->getEffects()->connectInputTo(
				outputs[0].name
			);

		_App->getSettingsLayout()->getInputDropdown()->setCurrentIndex( 1 );

	}

};


/**
 * @TODO
 */

void EffectLayout::takedown() {

	_App->getUI()
		->tabWidget->widget(0)->hide();

	_App->getUI()
		->tabWidget->widget(1)->hide();

};


/**
 * Load effect preset
 */

void EffectLayout::load( json j ) {

	Audio::Patchbay * host = _App->getServer()->getPatchbay();

	host->setActive( false );


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
