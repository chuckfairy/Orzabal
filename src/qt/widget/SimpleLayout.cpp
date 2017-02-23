/**
 * Simple layout start
 */
#include <Jack/Server.h>

#include <MainWindow.h>

#include "SimpleChangeEvent.h"
#include "SimpleLayout.h"


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

    std::cout << "TESTING CHANGE\n";

    LV2::Plugin * p = (LV2::Plugin*) data;

    Jack::Server * server = _App->getServer();

    server->getPatchbay()->addPlugin( p );

    _App->getUI()
        ->scrollArea->setWidget(
            p->getUI()->getControlWidget()
        );

    PLUGIN_SET = true;

    p->run();

};
