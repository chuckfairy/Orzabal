/**
 * Simple layout start
 */
#include <string.h>

#include <json/json.hpp>

#include "InstrumentEffect.h"

#include <Audio/UI.h>

#include <MainWindow.h>


using nlohmann::json;

using Orza::App::Widget::Patchbay;
using Orza::App::Widget::SingleInstrument;


namespace Orza { namespace App { namespace Layouts {

/**
 * Construct
 */

InstrumentEffect::InstrumentEffect( MainWindow * app ) :
    _App( app ),
    _SingleInstrument( new SingleInstrument( app ) ),
    _Patchbay( new Patchbay( app ) )
{
};


/**
 * Main virtuals
 */

void InstrumentEffect::setup() {

    //Patchbay setup

    _App->getUI()
        ->tabWidget->insertTab( 0, _SingleInstrument->getWidgetContainer(), "Instruments" );

    _App->getUI()
        ->tabWidget->insertTab( 1, _Patchbay->getWidgetContainer(), "Effects" );

    _App->getUI()->tabWidget->setCurrentIndex( 0 );

};


void InstrumentEffect::takedown() {

    _App->getUI()
        ->tabWidget->removeTab( 0 );

    _App->getUI()
        ->tabWidget->removeTab( 0 );

};

/**
 * Main layout load
 */

void InstrumentEffect::load( json j ) {

    Jack::Patchbay * host = _App->getServer()->getPatchbay();

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

}; }; };
