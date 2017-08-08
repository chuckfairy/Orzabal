/**
 * Simple layout start
 */
#pragma once

#include <json/json.hpp>

#include <Audio/PatchbayPresetLoader.h>

#include <LV2/Plugin.h>
#include <LV2/UI.h>
#include <Util/Dispatcher.h>

#include "InstrumentDropdown.h"

using nlohmann::json;

/**
 * Forwarding
 */

class MainWindow;

class SimpleLayout : public Audio::PatchbayPresetLoader {

    public:

        SimpleLayout( MainWindow * );

        void setEvents();

        void handleChange( void * );

        void load( json settings );


    private:

        InstrumentDropdown * _Dropdown;

        Util::Event * _ChangeEvent;

        LV2::Plugin * _CurrentPlugin;

        bool PLUGIN_SET = false;

        MainWindow * _App;


        /**
         * Main plugin setter
         */

        void setPlugin( LV2::Plugin * );

};
