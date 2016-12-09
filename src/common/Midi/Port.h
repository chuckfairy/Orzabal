/**
 * Midi Device
 *
 */
#pragma once

namespace Midi {

struct Port {

    const char * name;

    int card;

    int cardDevice;

    int subCardDevice;

    bool isInput;

    bool isOutput;

};

};
