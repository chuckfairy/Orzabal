/**
 * Start main qt window
 *
 */
#include <iostream>

#include <signal.h>
#include <QApplication>
#include "MainWindow.h"

using namespace std;

QApplication * app;

MainWindow * win;


//Signal handler if from CLI

static void signal_handler( int ignored ) {

    win->goWindowed();
    app->closeAllWindows();
    app->quit();

};


//Main startup using MainWindow

int main( int argc, char **argv ) {

    app = new QApplication(argc, argv);

    win = new MainWindow;

    win->show();

	signal( SIGINT, signal_handler );
	signal( SIGTERM, signal_handler );

    return app->exec();

}
