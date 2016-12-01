/**
 * ALSA midi helper
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#include <sndfile.h>

#include <vector>

#include "ALSA.h"

using std::vector;


namespace Midi {


/**
 * Construct
 *
 */

ALSA::ALSA() {};

int ALSA::isInput( snd_ctl_t *ctl, int card, int device, int sub ) {

    snd_rawmidi_info_t *info;
    int err;

    snd_rawmidi_info_alloca(&info);
    snd_rawmidi_info_set_device(info, device);
    snd_rawmidi_info_set_subdevice(info, sub);
    snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);

    if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0 && err != -ENXIO)
        return err;
    else if (err == 0)
        return 1;

    return 0;

};

int ALSA::isOutput( snd_ctl_t *ctl, int card, int device, int sub ) {

    snd_rawmidi_info_t *info;
    int err;

    snd_rawmidi_info_alloca(&info);
    snd_rawmidi_info_set_device(info, device);
    snd_rawmidi_info_set_subdevice(info, sub);
    snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);

    if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0 && err != -ENXIO) {

        return err;

    } else if (err == 0) {

        return 1;
    }

    return 0;

};


/**
 * Get midi device from card and device ints
 *
 */

vector<Device> ALSA::getDevicesFromCard(snd_ctl_t *ctl, int card, int device) {

    vector<Device> deviceReturn;

    snd_rawmidi_info_t *info;
    const char *name;
    const char *sub_name;
    int subs, subs_in, subs_out;
    int sub, in, out;
    int err;

    snd_rawmidi_info_alloca(&info);
    snd_rawmidi_info_set_device(info, device);

    snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
    snd_ctl_rawmidi_info(ctl, info);
    subs_in = snd_rawmidi_info_get_subdevices_count(info);
    snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
    snd_ctl_rawmidi_info(ctl, info);
    subs_out = snd_rawmidi_info_get_subdevices_count(info);
    subs = subs_in > subs_out ? subs_in : subs_out;

    sub = 0;
    in = out = 0;
    if ((err = isOutput(ctl, card, device, sub)) < 0) {
        //error("cannot get rawmidi information %d:%d: %s",
        //card, device, snd_strerror(err));
        return deviceReturn;
    } else if (err)
        out = 1;

    if (err == 0) {
        if ((err = isInput(ctl, card, device, sub)) < 0) {
            //error("cannot get rawmidi information %d:%d: %s",
            //card, device, snd_strerror(err));
            return deviceReturn;
        }
    } else if (err)
        in = 1;

    if (err == 0)
        return deviceReturn;

    name = snd_rawmidi_info_get_name(info);

    sub_name = snd_rawmidi_info_get_subdevice_name(info);

    if (sub_name[0] == '\0') {

        if (subs == 1) {
            printf("%c%c  hw:%d,%d    %s\n",
                    in ? 'I' : ' ', out ? 'O' : ' ',
                    card, device, name);
        } else {
            printf("%c%c  hw:%d,%d    %s (%d subdevices)\n",
                    in ? 'I' : ' ', out ? 'O' : ' ',
                    card, device, name, subs);
        }

        Device subDevice {
            name,
                card,
                device,
                0,
                (bool) in,
                (bool) out
        };

        deviceReturn.push_back( subDevice );

    } else {

        sub = 0;

        for (;;) {

            //Create and append devices
            //printf("%c%c  hw:%d,%d,%d  %s\n",
                    //in ? 'I' : ' ', out ? 'O' : ' ',
                    //card, device, sub, sub_name);

            Device subDevice {
                strdup( sub_name ),
                card,
                device,
                sub,
                isInput( ctl, card, device, sub ),
                isOutput( ctl, card, device, sub )
            };

            deviceReturn.push_back( subDevice );

            if( ++sub >= subs ) { break; }

            snd_rawmidi_info_set_subdevice(info, sub);

            if( subDevice.isOutput ) {
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
                if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0) {
                    //error("cannot get rawmidi information %d:%d:%d: %s",
                    //card, device, sub, snd_strerror(err));
                    break;
                }
            } else {
                snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
                if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0) {
                    //error("cannot get rawmidi information %d:%d:%d: %s",
                    //card, device, sub, snd_strerror(err));
                    break;
                }
            }
            sub_name = snd_rawmidi_info_get_subdevice_name(info);
        }
    }

    return deviceReturn;

};


/**
 * Get midi devices via card snd
 *
 */

vector<Device> ALSA::getCardDevices( int card ) {

    vector<Device> devices;

    snd_ctl_t *ctl;
    char name[32];
    int device;
    int err;

    sprintf(name, "hw:%d", card);

    if ((err = snd_ctl_open(&ctl, name, 0)) < 0) {

        return devices;

    }

    device = -1;

    for(;;) {

        if( ( err = snd_ctl_rawmidi_next_device( ctl, &device ) ) < 0 ) {

            break;

        } else if( device < 0 ) {

            break;

        }

        vector<Device> cardDevices = getDevicesFromCard(ctl, card, device);

        for( vector<Device>::iterator itVec = cardDevices.begin(); itVec != cardDevices.end(); ++itVec ) {

            devices.push_back( *itVec );

        }

    }

    snd_ctl_close( ctl );

    return devices;

};


/**
 * Get al cards snd
 *
 */

vector<Device> ALSA::getDevices() {

    vector<Device> devices;

    int card, err;

    card = -1;

    if ((err = snd_card_next(&card)) < 0) {

        //error("cannot determine card number: %s", snd_strerror(err));
        return devices;

    } else if (card < 0) {

        //error("no sound card found");
        return devices;

    }

    //puts("Dir Device    Name");

    while( card >= 0 ) {

        vector<Device> cardDevices = getCardDevices(card);

        for( vector<Device>::iterator itVec = cardDevices.begin(); itVec != cardDevices.end(); ++itVec ) {

            devices.push_back( *itVec );

        }

        if ( ( err = snd_card_next( &card ) ) < 0 ) {

            break;

        }

    }

    return devices;

};

};
