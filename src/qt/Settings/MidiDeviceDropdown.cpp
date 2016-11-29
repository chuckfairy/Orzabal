/**
 * Midi device drop down impl
 *
 */
#include "MidiDeviceDropdown.h"


/**
 * Constructor test
 *
 */
MidiDeviceDropdown::MidiDeviceDropdown() {

    //Searcher = new LV2Search();

    //connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    //addMidiDevice( &_placeholder );

    //vector<Plugin> plugins = Searcher->findAll();

    //vector<Plugin>::iterator it;

    //for( it = plugins.begin(); it != plugins.end(); ++it ) {

        //MidiDevice opt = { it->getName() };

        //addMidiDevice( &opt );

    //}

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
bool MidiDeviceDropdown::addMidiDevice( Device *device, const int order ) {

    addItem( device->name );

    //MidiDevices.push_back( device );

    return true;

};
