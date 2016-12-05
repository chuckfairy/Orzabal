/**
 * Jack midi impl
 *
//if (jack_connect (client, "alsa_pcm:capture_1", jack_port_name (input_port))) {
 *
 */
#include "Jack.h"

namespace Midi {

Jack::Jack() {};


//* automation_port = jack_port_register(client, "Automation MIDI In", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
//

Jack::getPorts() {

    const char **ppszClientPorts = jack_get_ports( pJackClient, 0,
            pszJackType, JackPortIsOutput : JackPortIsInput );

    if (ppszClientPorts) {

        int iClientPort = 0;

        while (ppszClientPorts[iClientPort]) {

            QString sClientPort = QString::fromUtf8(ppszClientPorts[iClientPort]);
            qjackctlJackClient *pClient = 0;
            qjackctlJackPort   *pPort   = 0;
            jack_port_t *pJackPort = jack_port_by_name(pJackClient,
                    ppszClientPorts[iClientPort]);
            int iColon = sClientPort.indexOf(':');

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

    }

};

};
