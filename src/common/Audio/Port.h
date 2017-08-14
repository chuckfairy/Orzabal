/**
 * Port struct base
 *
 */
#pragma once

#include <inttypes.h>
#include <string>

namespace Audio {

/**
 * Port types
 */

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

enum PortValueType {
	VALUE_FLOAT,
	VALUE_DOUBLE,
	VALUE_INT,
	VALUE_LONG,
	VALUE_UNKNOWN
};


/**
 * Main port struct
 */

struct Port {

    const char * name;

    std::string nameString;


    /**
     * Flags
     */

    bool isAudio;

    bool isControl;

    bool isInput;

    bool isOutput;


    /**
     * Value and value type
     */

	float control;

    PortValueType valueType;

	enum PortType type;

    enum PortFlow flow;

    float lowerBound;

    float upperBound;


    /**
     * Bound index
     */

    uint32_t index;

};

};
