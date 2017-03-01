/**
 * Settings layout tab
 */
#include <MainWindow.h>

#include "Layout.h"


namespace Orza { namespace Qt {  namespace Settings {


/**
 * Construct
 */

Layout::Layout( MainWindow * win ) {

    _App = win;


    _MidiDropdown = new MidiDeviceDropdown();

    _LeftOutput = new OutputDropdown( _App->getServer() );
    _RightOutput = new OutputDropdown( _App->getServer() );

};

}; }; };
