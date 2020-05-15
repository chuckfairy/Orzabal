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

using Orza::Widget::SingleInstrument;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace Layouts {


class InstrumentEffect : public Layout {

    public:

        InstrumentEffect( MainWindow *, SingleInstrument *, Orza::Widget::Patchbay *);
        InstrumentEffect( MainWindow *);


        /**
         * Virtuals
         */

        void setup();

        void takedown();

        void load( json settings );


    private:

        Orza::Widget::Patchbay * _Patchbay;

        SingleInstrument * _SingleInstrument;

        MainWindow * _App;

};

}; };
