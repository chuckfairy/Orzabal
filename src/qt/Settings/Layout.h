/**
 * Settings layout tab
 */
#pragma once

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

        MidiDeviceDropdown * _MidiDropdown;

        OutputDropdown * _LeftOutput;
        OutputDropdown * _RightOutput;


    public:

        Layout( MainWindow * );

};

}; }; };
