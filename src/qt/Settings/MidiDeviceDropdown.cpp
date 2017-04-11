/**
 * Midi device drop down impl
 *
 */
#include <vector>

#include <MainWindow.h>

#include <Jack/Port.h>
#include <Jack/Server.h>
#include <Jack/Midi.h>

#include "MidiDeviceDropdown.h"

using std::vector;


/**
 * Constructor test
 *
 */

MidiDeviceDropdown::MidiDeviceDropdown( MainWindow * win ) :
    QComboBox(),
    _App( win )
{

    vector<Jack::Port> ports = _App->getServer()
        ->getMidi()
        ->getMidiPorts();

    vector<Jack::Port>::iterator itVec;

    for( itVec = ports.begin(); itVec != ports.end(); ++itVec ) {

        addMidiDevice( &(*itVec) );

    }

};


/**
 * Add instrument implmentation
 * Will use list iterator
 *
 */
void MidiDeviceDropdown::addMidiDevice( Jack::Port * port , const int order ) {

    addItem( port->name );

    //MidiDevices.push_back( device );

};
