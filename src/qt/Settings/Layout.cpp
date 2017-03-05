/**
 * Settings layout tab
 */
#include <iostream>

#include <MainWindow.h>

#include "Events/OutputChangeEvent.h"
#include "Layout.h"


namespace Orza { namespace Qt {  namespace Settings {


/**
 * Construct
 */

Layout::Layout( MainWindow * win ) {

    _App = win;

    setDropdowns();
    setEvents();
    setAppUI();

};


/**
 * Set dropdown widgets and events
 */

void Layout::setDropdowns() {

    _LeftOutput = new OutputDropdown( _App->getServer() );
    _RightOutput = new OutputDropdown( _App->getServer() );

    _RightOutput->setCurrentIndex( 1 );

};


void Layout::setEvents() {

    _Event = (Util::Event*) new OutputChangeEvent( this );

    _LeftOutput->on( OutputDropdown::CHANGE_EVENT, _Event );
    _RightOutput->on( OutputDropdown::CHANGE_EVENT, _Event );

};

/**
 * Appp UI setting
 */

void Layout::setAppUI() {

    _App->getUI()->horizontalLayout_5->addWidget( _LeftOutput );
    _App->getUI()->horizontalLayout_5->addWidget( _RightOutput );

};


/**
 * Update output ports to selected inputs
 */

void Layout::updateOutputPorts() {

    const int left = _LeftOutput->currentIndex();
    const int right = _RightOutput->currentIndex();

    vector<Jack::Port> ports = _App->getServer()
        ->getAudio()
        ->getInputPorts();

    _App->getServer()
        ->getAudio()
        ->disconnectOutputs();

    _App->getServer()
        ->getAudio()
        ->connectOutputTo(
            ports[ left ].name,
            ports[ right ].name
        );

};

}; }; };
