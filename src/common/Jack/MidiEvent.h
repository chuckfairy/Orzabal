/**
 * Jack midi event impl
 */
#pragma once

#include <jack/jack.h>
#include <jack/midiport.h>
#include <unistd.h>

#include <Midi/Events.h>

namespace Jack {

struct MidiEvent : public Orza::Midi::Event {

    explicit MidiEvent( jack_midi_event_t * jackEvent ) {

        uint8_t intJackType = jackEvent->buffer[0] & 0xf0;
        channel = jackEvent->buffer[0] & 0xf;

        switch (intJackType) {

            case 0x90:
                //printf (" note on  (channel %2d): pitch %3d, velocity %3d", channel, jackEvent->buffer[1], jackEvent->buffer[2]);
                type = Orza::Midi::EVENT_NOTE_ON;
                pitch = jackEvent->buffer[1];
                velocity = jackEvent->buffer[2];
                break;

            case 0x80:
                //printf (" note off (channel %2d): pitch %3d, velocity %3d", channel, jackEvent->buffer[1], jackEvent->buffer[2]);
                type = Orza::Midi::EVENT_NOTE_OFF;
                pitch = jackEvent->buffer[1];
                velocity = jackEvent->buffer[2];
                break;

            case 0xb0:
                //printf (" control change (channel %2d): controller %3d, value %3d", channel, jackEvent->buffer[1], jackEvent->buffer[2]);
                type = Orza::Midi::EVENT_CONTROL_CHANGE;
                controlNumber = (int) jackEvent->buffer[1];
                controlValue = (int) jackEvent->buffer[2];
                //std::cout << controlNumber << " CONTROL NUMBER JACK \n";
                //std::cout << controlValue << " CONTROL VALUE JACK \n";
                break;

            default:
                break;

        }

    };

};

};
