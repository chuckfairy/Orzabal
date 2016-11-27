/**
 *
 * Instrument dropdown
 *
 */
#include <QtCore>
#include <QComboBox>

#include "InstrumentOption.h"
#include "InstrumentDropdown.h"

/**
 * Constructor test
 *
 */
InstrumentDropdown::InstrumentDropdown() {

    Searcher = new LV2Search();

    InstrumentOption TestOption { "Test" };
    InstrumentOption TestOption2 { "Test2" };

    addInstrument( &TestOption );
    addInstrument( &TestOption2 );

    vector<Plugin> plugins = Searcher->findAll();

    vector<Plugin>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++it ) {

        InstrumentOption opt = { it->getName() };

        addInstrument( &opt );

    }

}

/**
 * Constructor test
 *
 */
InstrumentDropdown::InstrumentDropdown( QWidget * parent ) : QComboBox( parent ) {

}


/**
 * Add instrument implmentation
 * Will use list iterator
 *
 */
bool InstrumentDropdown::addInstrument( InstrumentOption *instrument, const int order ) {

    addItem( instrument->name );

    //Instruments.insert( instrument );

    return true;

}
