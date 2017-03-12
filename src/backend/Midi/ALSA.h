/**
 * ALSA midi mod
 *
 */
#pragma once

#include <vector>
#include <alsa/asoundlib.h>
#include <alsa/control.h>
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

class ALSA : public Host {

    private:

        vector<int> _cards;

        snd_seq_t * _seqHandle;

        int _inputPort;

        int _outputPort;

        const char * _name = "orzabal-midi";


    public:

        ALSA();

        void start();

        vector<Plugin> setDevices();

        int isInput( snd_ctl_t *ctl, int card, int device, int sub );

        int isOutput( snd_ctl_t *ctl, int card, int device, int sub );

        vector<Device> getDevicesFromCard( snd_ctl_t *ctl, int card, int device );

        vector<Device> getCardDevices( int card );

        vector<Device> getDevices();

        void getSeqData();

        void createPorts();

};

};
