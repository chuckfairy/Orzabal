/**
 * Simple layout start
 */
#include <Jack/Server.h>
#include <LV2/UIDriver.h>

#include <MainWindow.h>

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

    Patchbay * p = new Patchbay( _App );

};

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

void  SimpleLayout::load( json j ) {

    // Plugins

    for( json::iterator it = j["data"]["effects"].begin(); it != j["data"]["effects"].end(); ++it ) {

        json effect = *it;

        /// get by ideffect["id"]

        // setPlugin

    }

};
