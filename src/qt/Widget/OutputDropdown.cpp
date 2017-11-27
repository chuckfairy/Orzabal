/**
 * Midi device drop down impl
 *
 */
#include <vector>

#include <Audio/Port.h>
#include <Jack/Port.h>

#include "OutputDropdown.h"


using std::vector;


namespace Orza { namespace App { namespace Widget {


/**
 * Constructor test
 *
 */

OutputDropdown::OutputDropdown( Jack::Server * server ) :
    AbstractIODropdown()
{

    connect(
        this,
        SIGNAL( currentIndexChanged( int ) ),
        this,
        SLOT( handleSelectionChanged( int ) )
    );

    setHost( server->getAudio() );

    Jack::Port blank;
    blank.name = "-- None --";

    addOutput( blank );

    updateOptions();

};


/**
 * Update ports from host and dropdown options
 */

void OutputDropdown::updateOptions() {

    vector<Jack::Port> ports = _Host->getInputPorts();

    vector<Jack::Port>::iterator itVec;

    for( itVec = ports.begin(); itVec != ports.end(); ++itVec ) {

        addOutput( *itVec );

    }

};


/**
 * Events
 */

const char * OutputDropdown::CHANGE_EVENT = "CHANGE";


/**
 * Add output implmentation
 *
 */
void OutputDropdown::addOutput( Jack::Port port, const int order ) {

    addItem( port.name );

    _ports.push_back( port );

};


/**
 * Main change handler
 */

void OutputDropdown::handleSelectionChanged( int index ) {

    dispatch( CHANGE_EVENT, (void*) (intptr_t) index );

};


/**
 * Get jack port name
 */

const char * OutputDropdown::getCurrentJackPort() {

    return _ports[ currentIndex() ].name;

};

}; }; };
