/**
 * Effect layout
 */
#pragma once

#include <Layouts/Layout.h>
#include <Widget/Patchbay.h>

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


    private:

        Patchbay * _Patchbay;

        MainWindow * _App;

};

}; }; };
