/**
 * Note and frequency helpers
 *
 * http://newt.phys.unsw.edu.au/jw/notes.html
 */
#pragma once

#include "Config/Frequency.h"
#include "Note.h"

namespace Orza { namespace Midi { namespace Frequency {

/**
 * Base frequency of A0 from A4
 */

inline const float_t getBaseFrequency(
    const float_t A4Frequency
) {

    //Assume 4 octaves making 2^4 == 16

    return A4Frequency / 16;

};


/**
 * Get frequencies from a midi note
 */

inline const float_t getFromNote(
    const NoteNumber midiNote,
    const float_t A4Frequency = DEFAULT_A4
) {

    const float_t A0Frequency = getBaseFrequency( A4Frequency );

    float_t output = A0Frequency * pow( 2.0, ( midiNote - 21 ) / 12 );

    return output;

};

}; }; };
