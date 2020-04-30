/**
 * Control tab layout
 */
#include <MainWindow.h>

#include "ControlTab.h"

/**
 * Forwarding
 */

class MainWindow;

namespace Orza { namespace MidiControl {

/**
 * Construct
 */

ControlTab::ControlTab( MainWindow * app ) :
	_App( app ),
	_Control( new Control( app->getServer() ) )
{

	_App->getUI()
		->tabWidget->insertTab( 0, _Control->getWidget(), "Control" );

};

}; };
