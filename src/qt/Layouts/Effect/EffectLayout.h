/**
 * Effect layout
 */
#pragma once

#include <Layouts/Layout.h>
#include <Widget/Patchbay.h>


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Layout {

class EffectLayout : public Layout {

    public:

        EffectLayout( MainWindow * );

    private:

        Patchbay * _Patchbay;

        MainWindow * _App;

};

}; }; };
