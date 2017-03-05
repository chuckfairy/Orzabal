/**
 * Output change event impl
 */
#include <Settings/Layout.h>

#include "OutputChangeEvent.h"


namespace Orza { namespace Qt {  namespace Settings {

/**
 * Construct
 */

OutputChangeEvent::OutputChangeEvent( Layout * l ) {

    _Layout = l;

};


/**
 * Change handler
 */

void OutputChangeEvent::run( void * data ) {

    _Layout->updateOutputPorts();

};

}; }; };
