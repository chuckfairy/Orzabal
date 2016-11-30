/**
 * Jack server class testing
 *
 */
#include <iostream>

#include <Server/JackServer.h>

#include <Midi/ALSA.h>

using namespace Midi;

int main() {

    //JackServer * server = new JackServer();
    Midi::ALSA * aser = new Midi::ALSA();

    vector<Midi::Device> a = aser->getDevices();

    for( vector<Midi::Device>::iterator itVec = a.begin(); itVec != a.end(); ++itVec ) {

        std::cout << itVec->name << "\n";

    }

    //server->start();

    //server->getPorts();

    //sleep(-1);

    return 0;

};
