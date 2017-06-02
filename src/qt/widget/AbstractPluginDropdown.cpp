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


namespace Orza { namespace App { namespace Widget {


/**
 * Constructor test
 *
 */

AbstractPluginDropdown::AbstractPluginDropdown( Jack::Server * s ) :
    _Server( s )
{

};


/**
 * Constructor test
 *
 */

AbstractPluginDropdown::AbstractPluginDropdown( QWidget * parent ) : QComboBox( parent ) {

};


/**
 * Add instrument implmentation
 * Will use list iterator
 *
 */

bool AbstractPluginDropdown::addPlugin( InstrumentOption *instrument, const int order ) {

    addItem( instrument->name );

    _plugins.push_back( instrument );

    return true;

};

} } };
