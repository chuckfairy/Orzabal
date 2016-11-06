/**
 * LADSPA port struct
 *
 */
#pragma once

struct LADSPAPort {

    const char * name;

    bool isAudio;

    bool isControl;

    bool isInput;

    bool isOutput;

    float lowerBound;

    float upperBound;

};
