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

    connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    addInstrument( &_placeholder );

    vector<Plugin> plugins = Searcher->findAll();

    vector<Plugin>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++it ) {

        InstrumentOption opt = { it->getName() };

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
 * Add instrument implmentation
 * Will use list iterator
 *
 */
bool InstrumentDropdown::addInstrument( InstrumentOption *instrument, const int order ) {

    addItem( instrument->name );

    Instruments.push_back( instrument );

    return true;

};
