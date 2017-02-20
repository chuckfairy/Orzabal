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


/**
 * Main change handler
 */

void InstrumentDropdown::handleSelectionChanged( int index ) {

    //Check if placeholder

    if( index == 0 ) { return; }


    LV2::Host * h = _Server->getPatchbay();
    h->addPluginByIndex( index );

    //QMessageBox* msg = new QMessageBox();
    //msg->setWindowTitle("Hello !");
    //msg->setText( currentText() );
    //msg->show();

};
