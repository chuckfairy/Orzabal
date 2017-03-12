
/**
 * Jack midi mod
 * automation_port = jack_port_register(client, "Automation MIDI In", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
 *
 */
#pragma once

#include <vector>
#include <jack/jack.h>
#include <jack/midiport.h>

#include <Midi/Device.h>
#include <Midi/Port.h>

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

        int _inputPort;

        int _outputPort;

        const char * _name = "orzabal-midi-jack";


        /**
         * Jack client pointer
         */

        jack_client_t * _jackClient;


    public:

        Jack();


        /**
         * Connection methods
         */

        void start();

        void createPorts();

        vector<Port> getPorts();


        /**
         * Abstract jack port connection method
         *
         */

        int connectJackPort( const char *, const char * );

        void connectOutputTo( const char * );

        void connectInputTo( const char * );


        /**
         * Jack related
         */

        void setJackClient( jack_client_t * j ) {

            _jackClient = j;

        };

};

};
