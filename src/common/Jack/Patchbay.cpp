/**
 * Jack host impl
 *
 */
#include <jack/jack.h>

#include "Server.h"
#include "Patchbay.h"
#include "Port.h"


namespace Jack {


/**
 * Construct
 */

Patchbay::Patchbay( jack_client_t * c ) {

    setJackClient( c );

};


/**
 * Server related
 */

void Patchbay::setServer( Server * s ) {

    _Server = s;

};


/**
 * Plugin port connector to server audio
 * @TODO support more than stereo
 *
 */

void Patchbay::connectPluginPorts( Audio::Plugin * p ) {

    //Get outputs

    vector<long> * ports = p->getOutputPorts();

    if( ports->empty() ) { return; }


    Jack::Host * audio = _Server->getAudio();

    //Stereo check

    if( ports->size() > 1 ) {

        std::cout << " CONNECTING PLUGIN PORTS \n";

        Jack::Port * portLeft = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        Jack::Port * portRight = (Jack::Port*) p->getPort(
            (*ports)[ 1 ]
        );

        const char * leftName = audio->getPortFullName( portLeft->name );

        std::cout << leftName << " " << portLeft->name << "\n";

        std::cout << jack_port_name( portLeft->jack_port ) << "\n";

        audio->connectInputTo(
            jack_port_name( portLeft->jack_port ),
            audio->getPortFullName( portRight->name )
        );

    } else {

        Jack::Port * portMono = (Jack::Port*) p->getPort(
            (*ports)[ 0 ]
        );

        audio->connectInputTo(
            audio->getPortFullName( portMono->name )
        );

    }

};

};
