/**
 * Settings layout tab
 */
#pragma once

#include "OutputDropdown.h"

/**
 * Forwading
 */

class MainWindow;

namespace Orza { namespace Qt {  namespace Settings {

/**
 * class
 */

class Layout {

    private:

        MainWindow * _App;

        /**
         * Widget dropdowns
         */

        OutputDropdown * _LeftOutput;
        OutputDropdown * _RightOutput;

        /**
         * Main event
         */

        Util::Event * _Event;


        /**
         * Private setters for cleaniness
         */

        void setDropdowns();

        void setEvents();

        void setAppUI();


    public:

        Layout( MainWindow * );

        void updateOutputPorts();

};

}; }; };
