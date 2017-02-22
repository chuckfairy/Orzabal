/**
 * Simple layout start
 */
#include <Jack/Server.h>

#include "SimpleLayout.h"


SimpleLayout::SimpleLayout( MainWindow * app ) {

    _App = app;

    _Dropdown = new InstrumentDropdown;

};

void SimpleLayout::setEvents() {

    _ChangeEvent = new SimpleChangeEvent( this );

    _Dropdown->on(
        InstrumentDropdown::CHANGE_EVENT,
        _ChangeEvent
    );

};

void SimpleLayout::handleChange( void * data ) {

    LV2::Plugin * p = (LV2::Plugin*) data;

    Jack::Server * server = _App->getServer();

    server->getPatchbay()->addPlugin( p );

    PLUGIN_SET = true;

};
