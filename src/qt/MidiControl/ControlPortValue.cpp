/**
 * ControlPortValue widget editor
 */
#include <string>

#include "ControlPortValue.h"

#include <Util/String.h>


using std::string;
using std::to_string;


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

ControlPortValue::ControlPortValue(
    Jack::MidiControlPort * midiPort,
    Audio::PluginPortContainer * container
) :
    _WidgetContent( new QWidget() ),
    _ControlPort( midiPort ),
    _PortContainer( container )
{

    _UI.setupUi( _WidgetContent );

    _UI.label->setText( _PortContainer->getName() );

    setValue();

    //Events

    connect( _UI.range_from, SIGNAL( editingFinished() ), this, SLOT( handleUpdateRange() ) );

    connect( _UI.range_to, SIGNAL( editingFinished() ), this, SLOT( handleUpdateRange() ) );

};


/**
 * Percision for floats
 */

unsigned int ControlPortValue::PERCISION = 4;


/**
 * Add port
 */

void ControlPortValue::updateRange() {

    _ControlPort->fromVal = fromVal;
    _ControlPort->toVal = toVal;

};


/**
 * Qt event update range
 */

void ControlPortValue::handleUpdateRange() {

    fromVal = _UI.range_from->text().toDouble();
    toVal = _UI.range_to->text().toDouble();

    updateRange();

};


/**
 * char
 */

void ControlPortValue::setValue() {

    fromVal = _PortContainer->port->controlRange[0];
    toVal = _PortContainer->port->controlRange[1];

    QValidator * dv = new QDoubleValidator( fromVal, toVal, PERCISION );

    string from = Util::String::fromFloat( fromVal, PERCISION );
    string toString = Util::String::fromFloat( toVal, PERCISION );

    _UI.range_from->setText( from.c_str() );
    _UI.range_to->setText( toString.c_str() );

    //_UI.range_from->setValidator( dv );
    //_UI.range_to->setValidator( dv );

    _ControlPort->fromVal = fromVal;
    _ControlPort->toVal = toVal;

};

} } };
