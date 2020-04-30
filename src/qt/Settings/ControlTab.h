/**
 * Control tab layout
 */
#pragma once

#include <MidiControl/Control.h>


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace MidiControl {


/**
 * Main class
 */

class ControlTab {

	public:

		ControlTab( MainWindow * );


	private:

		MainWindow * _App;

		Control * _Control;

};

}; };
