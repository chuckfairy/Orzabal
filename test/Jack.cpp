/**
 * Jack server class testing
 *
 */
#include <Server/JackServer.h>

#include <Midi/ALSA.h>

int main() {

    //JackServer * server = new JackServer();
    Midi::ALSA * aser = new Midi::ALSA();

    aser->deviceList();

    //server->start();

    //server->getPorts();

//sleep(-1);

    return 0;

};
