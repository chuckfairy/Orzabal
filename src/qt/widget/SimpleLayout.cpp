/**
 * Simple layout start
 */
#include <Jack/Server.h>
#include <LV2/UIDriver.h>

#include <MainWindow.h>

#include "SimpleChangeEvent.h"
#include "SimpleLayout.h"

#include <LV2/UIDriver.h>

using Orza::App::LV2UI::UIDriver;


SimpleLayout::SimpleLayout( MainWindow * app ) {

    _App = app;

    _Dropdown = new InstrumentDropdown( _App->getServer() );

    setEvents();

    _App->getUI()
        ->horizontalLayout_4->insertWidget( 0, _Dropdown );


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

    LV2::Plugin * p = (LV2::Plugin*) data;

    UIDriver * driver = new UIDriver( p->getUI() );

    p->getUI()->addDriver( driver );

    Jack::Server * server = _App->getServer();

    server->getPatchbay()->clearPlugins();

    server->getPatchbay()->addPlugin( p );

    //_App->getUI()
        //->scrollArea
        //->setWidget(
            //p->getUI()->getControlWidget()
        //);

    PLUGIN_SET = true;

    p->run();

};
