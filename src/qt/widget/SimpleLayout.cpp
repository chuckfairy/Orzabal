/**
 * Simple layout start
 */
#include <string.h>

#include <json/json.hpp>

#include <Jack/Server.h>

#include <Jack/Patchbay.h>

#include <LV2/UIDriver.h>

#include <MainWindow.h>

#include <Audio/PluginRepository.h>

#include "SimpleChangeEvent.h"
#include "SimpleLayout.h"

#include "SingleInstrument.h"

#include "Patchbay.h"

#include <LV2/UIDriver.h>

using nlohmann::json;

using Orza::App::LV2UI::UIDriver;
using Orza::App::Widget::Patchbay;
using Orza::App::Widget::SingleInstrument;


SimpleLayout::SimpleLayout( MainWindow * app ) {

    _App = app;

    _Dropdown = new InstrumentDropdown( _App->getPluginSearch() );

    setEvents();

    _App->getUI()
        ->horizontalLayout_4->insertWidget( 0, _Dropdown );


    //Patchbay setup

    _Patchbay = new Patchbay( _App );

    _App->getUI()
        ->tabWidget->insertTab( 1, _Patchbay->getWidgetContainer(), "Effects" );

};


/**
 * Event setter internal
 */

void SimpleLayout::setEvents() {

    _ChangeEvent = new SimpleChangeEvent<SimpleLayout>( this );

    _Dropdown->on(
        InstrumentDropdown::CHANGE_EVENT,
        _ChangeEvent
    );

};


/**
 * Main dropdown change event
 */

void SimpleLayout::handleChange( void * data ) {

    setPlugin( (Audio::Plugin*) data );

};


/**
 * Set plugin
 */

void SimpleLayout::setPlugin( Audio::Plugin * p ) {

    UIDriver * driver = new UIDriver( (LV2::UI*) p->getUI() );

    p->getUI()->addDriver( driver );

    Jack::Server * server = _App->getServer();

    server->getPatchbay()->clearPlugins();

    server->getPatchbay()->addPlugin( p );

    PLUGIN_SET = true;

    p->run();

    _App->getUI()
        ->scrollArea
        ->setWidget(
            driver->getControlWidget()
        );

};


/**
 * Main layout load
 */

void SimpleLayout::load( json j ) {

    //@TODO remove LV2 make normal host

    Jack::Patchbay * host = _App->getServer()->getPatchbay();

    host->setActive( false );


    if( ! j["instruments"].empty() ) {

        json instrument = j["instruments" ][ 0 ];

        std::string id = instrument["id"];

        Audio::Plugin * p = _App->getPluginSearch()->getById( id.c_str() );
        Audio::Plugin * clone = (Audio::Plugin*) p->clone();

        setPortsFromJSON( clone, instrument );

        setPlugin( clone );

    }

    host->setActive( true );

    return;


    // Plugin effects

    _Patchbay->clearPlugins();

    if( ! j["effects"].empty() ) {

        for( json::iterator it = j["effects"].begin(); it != j["effects"].end(); ++it ) {

            json effect = *it;

            std::string id = effect["id"];

            Audio::Plugin * p = _App->getPluginSearch()->getById( id.c_str() );

            _Patchbay->addPlugin( p->clone() );

            setPortsFromJSON( p, effect );

        }

    }

};
