/**
 * LADPSA plugin tests
 *
 */
#include <stdio.h>
#include <iostream>

#include <Server/JackServer.h>
#include <Audio/Search.h>
#include <LV2/Plugin.h>
#include <LV2/Search.h>
#include <QApplication>

using namespace std;

int main( int argc, char ** argv ) {

    QApplication app(argc, argv);

    JackServer * server = new JackServer();

    server->start();

    server->connectDefault();

    LV2::Host * host = new LV2::Host( server->getJackClient() );

    vector<Audio::Plugin*> plugins = host->findAllPlugins();

    plugins[200]->start();

    int exe = app.exec();

    sleep(50);

    //vector<Plugin>::iterator it;

    //for( int i = 0; i < 10; i ++ ) {

    //cout << plugins[i].getName() << "\n";

    //}

    //   for( it = plugins.begin(); it != plugins.end(); ++it ) {
    //
    //       cout << it->getName() << "\n";
    //
    //   }

    return 0;

};
