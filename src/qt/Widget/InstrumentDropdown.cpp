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

using Orza::PluginSearch::LoadedPlugins;


/**
 * Constructor test
 *
 */

InstrumentDropdown::InstrumentDropdown( LoadedPlugins * p ) :
    _PluginSearch( p )
{

    connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    addInstrument( &_placeholder );

    vector<Plugin*> plugins = _PluginSearch->getMidiInstruments();

    vector<Plugin*>::iterator it;

    for( it = plugins.begin(); it != plugins.end(); ++it ) {

        Audio::Plugin * p = (*it);

        InstrumentOption * opt = new InstrumentOption();

        opt->name = p->getName();
        opt->id = p->getID();

        addInstrument( opt );

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

    std::cout << Instruments[ index ]->name << "\n";

    Audio::Plugin * p = _PluginSearch->getById( Instruments[ index ]->id.c_str() );

    //std::cout << p->getName() << "\n";

    dispatch( CHANGE_EVENT, (void*) p );

};
