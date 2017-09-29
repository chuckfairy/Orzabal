/**
 * Midi device drop down impl
 *
 */
#include <vector>

#include <Audio/Port.h>
#include <Jack/Port.h>

#include "InputDropdown.h"


using std::vector;


/**
 * Constructor test
 *
 */

InputDropdown::InputDropdown( Jack::Server * server ) {

    connect(
        this,
        SIGNAL( currentIndexChanged( int ) ),
        this,
        SLOT( handleSelectionChanged( int ) )
    );

    setHost( server->getAudio() );

    Jack::Port blank;
    blank.name = "-- None --";

    addInput( blank );

    updateOptions();

};


/**
 * Get jack port name
 */

const char * InputDropdown::getCurrentJackPort() {

    return _ports[ currentIndex() ].name;

};


/**
 * Update ports from host and dropdown options
 */

void InputDropdown::updateOptions() {

    vector<Jack::Port> ports = _Host->getOutputPorts();

    vector<Jack::Port>::iterator itVec;

    for( itVec = ports.begin(); itVec != ports.end(); ++itVec ) {

        addInput( *itVec );

    }

};


/**
 * Constructor widget override
 *
 */

InputDropdown::InputDropdown( QWidget * parent ) : QComboBox( parent ) {

};


/**
 * Events
 */

const char * InputDropdown::CHANGE_EVENT = "CHANGE";


/**
 * Add output implmentation
 *
 */
void InputDropdown::addInput( Jack::Port port, const int order ) {

    addItem( port.name );

    _ports.push_back( port );

    //Inputs.push_back( device );

};


/**
 * Main change handler
 */

void InputDropdown::handleSelectionChanged( int index ) {

    dispatch( CHANGE_EVENT, (void*) (intptr_t) index );

};
