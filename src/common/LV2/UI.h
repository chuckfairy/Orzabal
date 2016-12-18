/**
 * Plugin UI
 *
 */
#pragma once

#include "Plugin.h"

namespace LV2 {

/**
 * UI use of lilv
 *
 */
class UI {

    private:

        LV2Plugin * _Plugin;

    public:

        UI( LV2Plugin * );

        void start();

        void stop();

}

};
