/**
 * Jack audio mod
 *
 */
#include <vector>
#include <iostream>
#include <string>


#include "Jack.h"

using std::string;
using std::vector;


/**
 * Midi Alsa extended class
 *
 */

namespace Audio {


Jack::Jack() {};


/**
 * Create with jack
 *
 */

Jack::Jack( jack_client_t * j ) {

    setJackClient( j );

};


/**
 *
 */

void Jack::start() {

};


/**
 * Jack register and create ports
 *
 */

void Jack::createPorts() {

    _inputLeft = jack_port_register(
        _jackClient,
        _inputLeftName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput,
        0
    );

    _inputRight = jack_port_register(
        _jackClient,
        _inputRightName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput,
        0
    );

    _outputLeft = jack_port_register(
        _jackClient,
        _outputLeftName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );

    _outputRight = jack_port_register(
        _jackClient,
        _outputRightName,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );

};


/**
 * Get global jack ports
 *
 */

vector<Port> Jack::getPorts() {

    vector<Port> ports;

    const char **ppszClientPorts = jack_get_ports(
        _jackClient,
        0,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsInput
    );

    int iClientPort = 0;

    while (ppszClientPorts[iClientPort]) {

        string clientName( ppszClientPorts[iClientPort] );

        Port p {
            ppszClientPorts[iClientPort]
        };

        int *pClient = 0;
        int *pPort   = 0;
        jack_port_t *pJackPort = jack_port_by_name(_jackClient, clientName.c_str() );
        int iColon = clientName.find(':');

        std::cout << clientName << "\n";

        if (pJackPort && iColon >= 0) {

            //QString sClientName = sClientPort.left(iColon);
            //QString sPortName   = sClientPort.right(sClientPort.length() - iColon - 1);
            //pClient = static_cast<qjackctlJackClient *> (findClient(sClientName));

            //if (pClient)
            //pPort = static_cast<qjackctlJackPort *> (pClient->findPort(sPortName));

            if (pClient == 0) {

                //pClient->setClientName(sClientName);

            }

            //if (pClient && pPort == 0) {

            //pPort = new qjackctlJackPort(pClient, pJackPort);
            //pPort->setPortName(sPortName);
            //iDirtyCount++;

            //}

            //if (pPort)
            //pPort->markClientPort(1);
        }

        iClientPort++;

    }

    return ports;

};

};
