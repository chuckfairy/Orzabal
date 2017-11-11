/**
 * Event types
 */
#pragma once

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


namespace Orza { namespace Midi {

/**
 * Event types
 */
enum EventType {
    EVENT_NOTE_ON,
    EVENT_NOTE_OFF,
    EVENT_CONTROL_CHANGE,
    EVENT_UNKNOWN
};


/**
 * Midi event struct type
 */

struct Event {

    EventType type = EVENT_UNKNOWN;

    uint8_t channel;

    uint8_t pitch;

    uint8_t velocity;

    uint8_t controlNumber;

    uint8_t controlValue;


    /**
     * Type name getter
     * @TODO Make better
     */

    const char * getTypeName() {

        const char * EventTypeNames[] = {
            "Note On",
            "Note Off",
            "Control Change",
            "Unknnown"
        };

        return EventTypeNames[ type ];

    };

};

}; };
