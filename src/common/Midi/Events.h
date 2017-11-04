/**
 * Event types
 */
#pragma once


namespace Orza { namespace Midi {

/**
 * Event types
 */
enum EventType {
    EVENT_NOTE_ON,
    EVENT_NOTE_OFF,
    EVENT_CONTROL_CHANGE,
};


/**
 * Midi event struct type
 */

struct Event {

    Event( EventType t ) : type( t ) {};

    EventType type;

    unsigned int channel;

    unsigned int pitch;

    unsigned int velocity;

    unsigned int controlValue;

};

}; };
