/**
 * ALSA midi mod
 *
 */
#pragma once

#include <vector>

#include "Host.h"
#include "Plugin.h"

using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Midi {

class ALSA : public Host {

    public:

        ALSA();

        vector<Plugin> setDevices();


};

};
