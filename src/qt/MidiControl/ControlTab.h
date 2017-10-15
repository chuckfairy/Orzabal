/**
 * Control tab layout
 */
#pragma once

#include "Control.h"


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace MidiControl {


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

}; }; };
