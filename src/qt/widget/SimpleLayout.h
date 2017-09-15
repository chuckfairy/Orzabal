/**
 * Simple layout start
 */
#pragma once

#include <json/json.hpp>

#include <Audio/PatchbayPresetLoader.h>

#include <Util/Dispatcher.h>

#include "Patchbay.h"

#include "InstrumentDropdown.h"

using nlohmann::json;

using Orza::App::Widget::Patchbay;


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

        Patchbay * _Patchbay;

        Util::Event * _ChangeEvent;

        Audio::Plugin * _CurrentPlugin;

        bool PLUGIN_SET = false;

        MainWindow * _App;


        /**
         * Main plugin setter
         */

        void setPlugin( Audio::Plugin * );

};
