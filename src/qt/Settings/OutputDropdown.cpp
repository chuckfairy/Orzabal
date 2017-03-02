/**
 * Midi device drop down impl
 *
 */
#include <vector>

#include <Audio/Port.h>
#include <Jack/Port.h>

#include "OutputDropdown.h"


using std::vector;


/**
 * Constructor test
 *
 */

OutputDropdown::OutputDropdown( Jack::Server * server ) {

    connect(
        this,
        SIGNAL( currentIndexChanged( int ) ),
        this,
        SLOT( handleSelectionChanged( int ) )
    );

    setHost( server->getAudio() );

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
 * Constructor widget override
 *
 */
OutputDropdown::OutputDropdown( QWidget * parent ) : QComboBox( parent ) {};


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

    //Outputs.push_back( device );

};


/**
 * Main change handler
 */

void OutputDropdown::handleSelectionChanged( int index ) {

    dispatch( CHANGE_EVENT, (void*) (intptr_t) index );

};
