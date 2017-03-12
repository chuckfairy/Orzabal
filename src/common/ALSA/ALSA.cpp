/**
 * ALSA midi helper
 *
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
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


void ALSA::getSeqData() {

    snd_seq_t *pAlsaSeq;

    snd_seq_open(&pAlsaSeq, "hw", SND_SEQ_OPEN_DUPLEX, 0);
    snd_seq_set_client_name(pAlsaSeq, "ALSA Sequencer Demo");

	snd_seq_client_info_t *pClientInfo;
	snd_seq_port_info_t   *pPortInfo;

	snd_seq_client_info_alloca(&pClientInfo);
	snd_seq_port_info_alloca(&pPortInfo);
	snd_seq_client_info_set_client(pClientInfo, -1);

    unsigned int counter = 0;

	int i = snd_seq_query_next_client(pAlsaSeq, pClientInfo);

    std::cout << i << "\n";

    const int iAlsaClient = snd_seq_client_info_get_client(pClientInfo);

    if( iAlsaClient > 0 ) {

        std::cout << "HERE";

        //qjackctlAlsaClient *pClient = findClient(iAlsaClient);

        snd_seq_port_info_set_client(pPortInfo, iAlsaClient);
        snd_seq_port_info_set_port(pPortInfo, -1);

        const char * sClientName;

        while (snd_seq_query_next_port(pAlsaSeq, pPortInfo) >= 0) {

            const unsigned int uiPortCapability = snd_seq_port_info_get_capability(pPortInfo);

            if ( SND_SEQ_PORT_CAP_NO_EXPORT ) {

                snd_seq_client_info_get_name(pClientInfo);
                printf("%c:", iAlsaClient);
                int * pPort = 0;
                const int iAlsaPort = snd_seq_port_info_get_port(pPortInfo);
                if (counter == 0) {
                    //pClient = new qjackctlAlsaClient(this, iAlsaClient);
                    //pClient->setClientName(sClientName);
                    counter++;
                } else {
                    //pPort = pClient->findPort(iAlsaPort);
                    //if (sClientName != pClient->clientName()) {
                    //pClient->setClientName(sClientName);
                    counter++;
                    //}
                }

                char * sPortName;
                sprintf(
                        sPortName,
                        "%d:%s",
                        iAlsaPort,
                        snd_seq_port_info_get_name( pPortInfo )
                       );
                std::cout << sPortName;
                if (pPort == 0) {
                    //pPort = new qjackctlAlsaPort(pClient, iAlsaPort);
                    //pPort->setPortName(sPortName);
                    counter++;
                }

                if (pPort) {
                    //pPort->markClientPort(1);
                }

            }

        }

    }

};


/**
 * Start midi seq asound
 *
 */

void ALSA::start() {

    int result = snd_seq_open(&_seqHandle, "hw", SND_SEQ_OPEN_DUPLEX, 0);

    if( result < 0 ) {

        fprintf(stderr, "Error opening ALSA sequencer.\n");

        return;

    }

    snd_seq_set_client_name( _seqHandle, _name );

};


/**
 * Create ports for routing
 *
 */

void ALSA::createPorts() {

    start();

    _inputPort = snd_seq_create_simple_port(
        _seqHandle,
        _name,
        SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
        SND_SEQ_PORT_TYPE_APPLICATION
    );

};

};
