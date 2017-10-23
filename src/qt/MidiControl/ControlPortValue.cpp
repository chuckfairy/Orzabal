/**
 * ControlPortValue widget editor
 */
#include "ControlPortValue.h"

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


    //Events

    //connect( _UI.add_btn, SIGNAL( clicked() ), this, SLOT( addControlPortValueValue() ) );

};


/**
 * Add port
 */

void ControlPortValue::updateRange() {

};

} } };


