
/**
 * Jack midi mod
 * automation_port = jack_port_register(client, "Automation MIDI In", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
 *
 */
#pragma once

#include <vector>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

#include <Midi/Device.h>

#include "Host.h"
#include "Plugin.h"

using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Midi {

class Jack : public Host {

    private:

        vector<int> _cards;

        snd_seq_t * _seqHandle;

        int _inputPort;

        int _outputPort;

        const char * _name = "gabrielo-midi-jack";


    public:

        Jack();

        void start();

        void createPorts();

};

};
