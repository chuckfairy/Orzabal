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
    Jack::Midi * midi,
    Jack::MidiControlPort * midiPort,
    Audio::PluginPortContainer * container
) :
    _WidgetContent( new QWidget() ),
    _Midi( midi ),
    _ControlPort( midiPort ),
    _PortContainer( container )
{

    _UI.setupUi( _WidgetContent );

    _UI.label->setText( _PortContainer->getName() );

    _ControlRange = new Audio::MidiControlRange<Jack::MidiControlPort>( midiPort, container );

    setEvents();

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

};


/**
 * Qt event update range
 */

void ControlPortValue::handleUpdateRange() {

    _ControlRange->setMin( _UI.range_from->text().toDouble() );
    _ControlRange->setMax( _UI.range_to->text().toDouble() );

    updateRange();

};


/**
 * char
 */

void ControlPortValue::setValue() {

    _ControlRange->setMin( _PortContainer->port->controlRange[0] );
    _ControlRange->setMax( _PortContainer->port->controlRange[1] );

    //QValidator * dv = new QDoubleValidator( fromVal, toVal, PERCISION );

    string from = Util::String::fromFloat( _ControlRange->getMin(), PERCISION );
    string toString = Util::String::fromFloat( _ControlRange->getMax(), PERCISION );

    _UI.range_from->setText( from.c_str() );
    _UI.range_to->setText( toString.c_str() );

    //_UI.range_from->setValidator( dv );
    //_UI.range_to->setValidator( dv );


};


/**
 * Event midi message setting
 */

void ControlPortValue::setEvents() {

    _Event = new Midi::EventMessage<ControlPortValue>( this );


    //@TODO possibly make better naming

    const char * eventName = jack_port_name( _ControlPort->port->jack_port );

    _Midi->on( eventName, _Event );

};


/**
 * Midi message update
 */

void ControlPortValue::onMidiMessage( Orza::Midi::Event * event ) {

    std::cout << event->controlValue << "\n";

};

} } };
