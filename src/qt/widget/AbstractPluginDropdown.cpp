/**
 *
 * Instrument dropdown
 *
 */
#include <QtCore>
#include <QComboBox>

#include "InstrumentOption.h"
#include "AbstractPluginDropdown.h"

using Audio::Plugin;


/**
 * Constructor test
 *
 */

AbstractPluginDropdown::AbstractPluginDropdown( Jack::Server * s ) {

    _Server = s;

    connect( this, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handleSelectionChanged( int ) ) );

    addInstrument( &_placeholder );

    LV2::Host * host = _Server->getPatchbay();

    vector<Plugin*> plugins = host->findAllInstruments();

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

AbstractPluginDropdown::AbstractPluginDropdown( QWidget * parent ) : QComboBox( parent ) {

};


/**
 * Static setting
 * event related
 */

const char * AbstractPluginDropdown::CHANGE_EVENT = "CHANGE";


/**
 * Add instrument implmentation
 * Will use list iterator
 *
 */

bool AbstractPluginDropdown::addInstrument( InstrumentOption *instrument, const int order ) {

    addItem( instrument->name );

    Instruments.push_back( instrument );

    return true;

};


/**
 * Main change handler
 */

void AbstractPluginDropdown::handleSelectionChanged( int index ) {

    //Check if placeholder

    if( index == 0 ) { return; }


    LV2::Host * h = _Server->getPatchbay();
    Audio::Plugin * p = h->getPluginByIndex( index - 1 );

    dispatch( CHANGE_EVENT, (void*) p );

    //QMessageBox* msg = new QMessageBox();
    //msg->setWindowTitle("Hello !");
    //msg->setText( currentText() );
    //msg->show();

};
