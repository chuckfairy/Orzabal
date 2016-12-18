/**
 * Midi device drop down impl
 *
 */
#include <vector>

#include <Audio/Port.h>

#include "OutputDropdown.h"


using std::vector;

using Audio::Port;


/**
 * Constructor test
 *
 */

OutputDropdown::OutputDropdown( JackServer * server ) {

    setHost( server->getAudio() );

    updateOptions();

};


/**
 * Update ports from host and dropdown options
 */

void OutputDropdown::updateOptions() {

    vector<Port> ports = _Host->getInputPorts();

    for( vector<Port>::iterator itVec = ports.begin(); itVec != ports.end(); ++itVec ) {

        addOutput( *itVec );

    }

};


/**
 * Constructor widget override
 *
 */
OutputDropdown::OutputDropdown( QWidget * parent ) : QComboBox( parent ) {};


/**
 * Add output implmentation
 *
 */
void OutputDropdown::addOutput( Port port, const int order ) {

    addItem( port.name );

    //Outputs.push_back( device );

};
