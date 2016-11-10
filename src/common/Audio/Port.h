/**
 * Port struct base
 *
 */
#pragma once

struct Port {

    const char * name;

    bool isAudio;

    bool isControl;

    bool isInput;

    bool isOutput;

    float lowerBound;

    float upperBound;

};
