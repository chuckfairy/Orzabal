/**
 *
 * Instrument dropdown
 *
 */
#include "InstrumentOption.h"
#include "InstrumentDropdown.h"


/**
 * Constructor test
 *
 */
InstrumentDropdown::InstrumentDropdown() {

    InstrumentOption TestOption { "Test" };
    InstrumentOption TestOption2 { "Test2" };

    addInstrument( TestOption );
    addInstrument( TestOption2 );

}


/**
 * Add instrument implmentation
 * Will use list iterator
 *
 */
bool InstrumentDropdown::addInstrument( InstrumentOption instrument, const int order ) {

    addItem( instrument.name );

    Instrument.insert( instrument );

}
