/**
 *
 * Instrument dropdown
 *
 */
#include <QtCore>
#include <QComboBox>

#include "InstrumentOption.h"
#include "InstrumentDropdown.h"

using Audio::Plugin;


/**
 * Constructor test
 *
 */

InstrumentDropdown::InstrumentDropdown( Jack::Server * s ) {

    _Server = s;

    connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    addInstrument( &_placeholder );

    LV2::Host * host = _Server->getPatchbay();

    vector<Plugin*> plugins = host->getSearch()->findMidiInstruments();

    vector<Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++it ) {

        LV2::Plugin * p = (LV2::Plugin*) (*it);

        InstrumentOption opt = {
            p->getName(),
            p->getURI()
        };

        addInstrument( &opt );

    }

};


/**
 * Constructor test
 *
 */

InstrumentDropdown::InstrumentDropdown( QWidget * parent ) : QComboBox( parent ) {

};


/**
 * Static setting
 * event related
 */

const char * InstrumentDropdown::CHANGE_EVENT = "CHANGE";


/**
 * Add instrument implmentation
 * Will use list iterator
 *
 */

bool InstrumentDropdown::addInstrument( InstrumentOption *instrument, const int order ) {

    addItem( instrument->name );

    Instruments.push_back( instrument );

    return true;

};


/**
 * Main change handler
 */

void InstrumentDropdown::handleSelectionChanged( int index ) {

    //Check if placeholder

    if( index == 0 ) { return; }


    LV2::Host * h = _Server->getPatchbay();
    vector<Audio::Plugin*> plugins = h->getSearch()->findMidiInstruments();
    Audio::Plugin * p = plugins[ index - 1 ];

    //std::cout << p->getName() << "\n";

    dispatch( CHANGE_EVENT, (void*) p );

};
