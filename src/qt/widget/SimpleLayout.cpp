/**
 * Simple layout start
 */
#include <string.h>

#include <json/json.hpp>

#include <Jack/Server.h>
#include <LV2/UIDriver.h>

#include <MainWindow.h>

#include <Audio/PluginRepository.h>

#include "SimpleChangeEvent.h"
#include "SimpleLayout.h"

#include "Patchbay.h"

#include <LV2/UIDriver.h>

using nlohmann::json;

using Orza::App::LV2UI::UIDriver;
using Orza::App::Widget::Patchbay;


SimpleLayout::SimpleLayout( MainWindow * app ) {

    _App = app;

    _Dropdown = new InstrumentDropdown( _App->getServer() );

    setEvents();

    _App->getUI()
        ->horizontalLayout_4->insertWidget( 0, _Dropdown );

    _Patchbay = new Patchbay( _App );

};


/**
 * Event setter internal
 */

void SimpleLayout::setEvents() {

    _ChangeEvent = new SimpleChangeEvent( this );

    _Dropdown->on(
        InstrumentDropdown::CHANGE_EVENT,
        _ChangeEvent
    );

};


/**
 * Main dropdown change event
 */

void SimpleLayout::handleChange( void * data ) {

    setPlugin( (LV2::Plugin*) data );

};


/**
 * Set plugin
 */

void SimpleLayout::setPlugin( LV2::Plugin * p ) {

    UIDriver * driver = new UIDriver( p->getUI() );

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

    LV2::Host * host = _App->getServer()->getPatchbay();

    host->setActive( false );


    if( ! j["instruments"].empty() ) {

        json instrument = j["instruments" ][ 0 ];

        std::string id = instrument["id"];

        Audio::Plugin * p = host->getSearch()->findById( id.c_str() );
        LV2::Plugin * clone = (LV2::Plugin*) p->clone();

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

            Audio::Plugin * p = host->getSearch()->findById( id.c_str() );

            _Patchbay->addPlugin( p->clone() );

            setPortsFromJSON( p, effect );

        }

    }

};
