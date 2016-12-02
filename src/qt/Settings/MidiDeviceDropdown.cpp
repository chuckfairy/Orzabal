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

    midiDriver = new Midi::ALSA();

    vector<Midi::Device> devices = midiDriver->getDevices();

    for( vector<Midi::Device>::iterator itVec = devices.begin(); itVec != devices.end(); ++itVec ) {

        addMidiDevice( *itVec );

    }

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
void MidiDeviceDropdown::addMidiDevice( Device device, const int order ) {

    addItem( device.name );

    //MidiDevices.push_back( device );

};
