/**
 * Control tab layout
 */
#include <MainWindow.h>

#include "ControlTab.h"

/**
 * Forwarding
 */

namespace Orza { namespace MidiControl {

/**
 * Construct
 */

ControlTab::ControlTab( MainWindow * app ) :
	_App( app ),
	_Control( new Control( app->getServer() ) )
{

	_App->acceptDrops();
	_App->getUI()
		->tabWidget->insertTab( 2, _Control->getWidget(), "Control" );

};

}; };
