/**
 * Simple layout start
 */
#pragma once

#include <Layouts/Layout.h>

#include <json/json.hpp>

#include <Audio/PatchbayPresetLoader.h>

#include <Util/Dispatcher.h>

#include <Widget/Patchbay.h>

#include <Widget/SingleInstrument.h>

using nlohmann::json;

using Orza::App::Widget::Patchbay;
using Orza::App::Widget::SingleInstrument;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Layouts {


class InstrumentEffect : public Layout {

    public:

        InstrumentEffect( MainWindow * );


        /**
         * Virtuals
         */

        void setup();

        void takedown();

        void load( json settings );


    private:

        Patchbay * _Patchbay;

        SingleInstrument * _SingleInstrument;

        MainWindow * _App;

};

}; }; };
