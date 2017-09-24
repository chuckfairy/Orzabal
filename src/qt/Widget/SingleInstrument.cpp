/**
 * Single instrument widget
 */
#include <LV2/UIDriver.h>

#include <MainWindow.h>

#include "SingleInstrument.h"

#include "SimpleChangeEvent.h"


using std::vector;

using Orza::App::LV2UI::UIDriver;


namespace Orza { namespace App { namespace Widget {


/**
 * Main class
 */

SingleInstrument::SingleInstrument( MainWindow * app ) :
    _App( app ),
    _Dropdown( new InstrumentDropdown( app->getPluginSearch() ) ),
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );

    _UI.item_area->addWidget( _Dropdown );

    setEvents();

};


/**
 * Event setter internal
 */

void SingleInstrument::setEvents() {

    Util::Event * e = new SimpleChangeEvent<SingleInstrument>( this );

    _Dropdown->on(
        InstrumentDropdown::CHANGE_EVENT,
        e
    );

};


/**
 * Clear plugin
 */

void SingleInstrument::clearPlugin() {

};


/**
 * Set plugin and driver
 */

void SingleInstrument::setPlugin( Audio::Plugin * p ) {

    UIDriver * driver = new UIDriver( (LV2::UI*) p->getUI() );

    p->getUI()->addDriver( driver );

    Jack::Server * server = _App->getServer();

    server->getPatchbay()->clearPlugins();

    server->getPatchbay()->addPlugin( p );

    HAS_PLUGIN = true;

    p->run();

    _UI.singleinstrument_scroll_area
        ->setWidget(
            driver->getControlWidget()
        );

};


/**
 * Main dropdown change event
 */

void SingleInstrument::handleChange( void * data ) {

    setPlugin( (Audio::Plugin*) data );

};

}; }; };
