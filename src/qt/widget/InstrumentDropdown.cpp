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

    InstrumentOption TestOption { "Test" };
    InstrumentOption TestOption2 { "Test2" };

    addInstrument( &TestOption );
    addInstrument( &TestOption2 );

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
