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

    ALSA * aser = new ALSA();

    aser->getSeqData();

    //vector<Midi::Device> a = aser->getDevices();

    //for( vector<Midi::Device>::iterator itVec = a.begin(); itVec != a.end(); ++itVec ) {

        //std::cout << itVec->name << "\n";

    //}


    //JackServer * server = new JackServer();

    //server->start();

    //sleep( 50 );

    //server->stop();

    //server->getPorts();

    return 0;

};
