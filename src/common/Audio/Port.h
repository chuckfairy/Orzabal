/**
 * Port struct base
 *
 */
#pragma once

#include <inttypes.h>
#include <string>

namespace Audio {

enum PortFlow {
	FLOW_UNKNOWN,
	FLOW_INPUT,
	FLOW_OUTPUT
};

enum PortType {
	TYPE_UNKNOWN,
	TYPE_CONTROL,
	TYPE_AUDIO,
	TYPE_EVENT,
	TYPE_CV
};

struct Port {

    const char * name;

    bool isAudio;

    bool isControl;

    bool isInput;

    bool isOutput;

	enum PortType type;

	enum PortFlow flow;

	float control;

    float lowerBound;

    float upperBound;

    uint32_t index;

    std::string nameString;

};

};
