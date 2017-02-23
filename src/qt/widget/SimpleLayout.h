/**
 * Simple layout start
 */
#pragma once

#include <LV2/Plugin.h>
#include <LV2/UI.h>
#include <Util/Dispatcher.h>

#include "InstrumentDropdown.h"

/**
 * Forwarding
 */

class MainWindow;

class SimpleLayout {

    private:

        InstrumentDropdown * _Dropdown;

        Util::Event * _ChangeEvent;

        LV2::Plugin * _CurrentPlugin;

        bool PLUGIN_SET = false;

        MainWindow * _App;


    public:

        SimpleLayout( MainWindow * );

        void setEvents();

        void handleChange( void * );

};
