/**
 * Midi device drop down impl
 *
 */
#include <vector>

#include "MidiDeviceDropdown.h"

using std::vector;


/**
 * Constructor test
 *
 */

MidiDeviceDropdown::MidiDeviceDropdown() {


};


/**
 * Constructor test
 *
 */
MidiDeviceDropdown::MidiDeviceDropdown( QWidget * parent ) : QComboBox( parent ) {

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
