/**
 * Effect layout
 */
#pragma once

#include <json/json.hpp>

#include <Layouts/Layout.h>
#include <Widget/Patchbay.h>


using nlohmann::json;

using Orza::App::Widget::Patchbay;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Layouts {

class EffectLayout : public Layout {

    public:

        EffectLayout( MainWindow * );

        /**
         * Virtuals
         */

        void setup();

        void takedown();

        void load( json j );


    private:

        Patchbay * _Patchbay;

        MainWindow * _App;

};

}; }; };
