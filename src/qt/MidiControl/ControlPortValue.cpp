/**
 * ControlPortValue widget editor
 */
#include "ControlPortValue.h"

namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

ControlPortValue::ControlPortValue( Audio::Port * u, Audio::Port * effectPort ) :
    _WidgetContent( new QWidget() )
{

    _UI.setupUi( _WidgetContent );


    //Events

    //connect( _UI.add_btn, SIGNAL( clicked() ), this, SLOT( addControlPortValueValue() ) );

};


/**
 * Add port
 */

void ControlPortValue::updateRange() {

};

} } };


