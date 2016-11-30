/**
 * Midi Device
 *
 */
#pragma once

namespace Midi {

struct Device {

    const char * name;

    int card;

    int cardDevice;

    int subCardDevice;

    bool isInput;

    bool isOutput;

};

};
