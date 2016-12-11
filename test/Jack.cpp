/**
 * Jack server class testing
 *
 */
#include <iostream>

#include <Server/JackServer.h>

#include <Midi/ALSA.h>
#include <Midi/Jack.h>

#include <Audio/Jack.h>

using namespace Midi;

int main() {

    JackServer * server = new JackServer();

    //ALSA * aser = new ALSA();

    //aser->createPorts();

    server->start();

    server->connectDefault();

    sleep(50);

    //Midi::Jack * j = new Midi::Jack();

    //j->setJackClient( server->getJackClient() );

    //j->getPorts();

    //vector<Midi::Device> a = aser->getDevices();

    //for( vector<Midi::Device>::iterator itVec = a.begin(); itVec != a.end(); ++itVec ) {

        //std::cout << itVec->name << "\n";

    //}


    //JackServer * server = new JackServer();

    //server->start();

    //server->stop();

    //server->getPorts();

    return 0;

};
