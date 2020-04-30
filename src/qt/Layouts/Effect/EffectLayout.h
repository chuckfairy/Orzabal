/**
 * Effect layout
 */
#pragma once

#include <json/json.hpp>

#include <Layouts/Layout.h>
#include <Widget/Patchbay.h>


using nlohmann::json;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace Layouts {


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

        Orza::Widget::Patchbay * _Patchbay;

        MainWindow * _App;

};

}; };
