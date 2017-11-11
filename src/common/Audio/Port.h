/**
 * Port struct base
 *
 */
#pragma once

#include <map>
#include <vector>
#include <inttypes.h>
#include <string>


using std::map;
using std::vector;


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

enum PortControlValueType {
	CONTROL_VALUE_ENUM,
	CONTROL_VALUE_LOG,
	CONTROL_VALUE_INT,
    CONTROL_VALUE_BOOL,
	CONTROL_VALUE_UNKNOWN
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

    bool isAudio = false;

    bool isControl = false;

    bool isInput = false;

    bool isOutput = false;


    /**
     * Value and value type
     */

	float control = 0;

    PortValueType valueType = VALUE_UNKNOWN;

	enum PortType type = TYPE_UNKNOWN;

    enum PortFlow flow = FLOW_UNKNOWN;

    float lowerBound = 0;

    float upperBound = 0;


    /**
     * Control types
     */

    PortControlValueType controlValueType = CONTROL_VALUE_UNKNOWN;

    vector<float> controlRange;

    map<float, const char*> scaleMap;

    vector<float> scalePoints;

    int steps;


    /**
     * Bound index
     */

    uint32_t index = 0;

};

};
