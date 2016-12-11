/**
 * Jack midi impl
 *
//if (jack_connect (client, "alsa_pcm:capture_1", jack_port_name (input_port))) {
 *
 */
#include <iostream>
#include <string>

#include "Jack.h"

using std::string;


namespace Midi {

Jack::Jack() {};


//* automation_port = jack_port_register(client, "Automation MIDI In", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
//

vector<Port> Jack::getPorts() {

    vector<Port> ports;

    const char **ppszClientPorts = jack_get_ports(
        _jackClient,
        0,
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput
    );
    //: JackPortIsInput

    if( ! ppszClientPorts) {

        return ports;

    }


    int iClientPort = 0;

    while( ppszClientPorts[iClientPort] ) {

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

    free(ppszClientPorts);

    return ports;

};

};
