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

    int channel = 1;

    int pitch = 0;

    int velocity = 0;

    int controlNumber = 0;

    int controlValue = 0;


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
