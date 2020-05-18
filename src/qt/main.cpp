/**
 * Start main qt window
 *
 */
#include <iostream>

#include <signal.h>
#include <QApplication>
#include <cli/App.h>
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

#ifdef IS_PI

#include <pi/Config/Commands.h>

static void startVNC() {
	system(Orza::Pi::Config::VNC_STARTUP);
}

static void stopVNC() {
	system(Orza::Pi::Config::VNC_STOP);
}
#endif


//Main startup using MainWindow

int main( int argc, char **argv ) {

	Orza::CLI::App * cli = new Orza::CLI::App( argc, argv );

	cli->displayDefault();

	if( ! cli->isMainProgram() ) {

		return 0;

	}

	cli->displayHeader();


	// Qt app

#ifdef IS_PI
	startVNC();
#endif

	app = new QApplication(argc, argv);

	win = new MainWindow( app );

	win->show();

	signal( SIGINT, signal_handler );
	signal( SIGTERM, signal_handler );

	int out = app->exec();

#ifdef IS_PI
	stopVNC();
#endif

	return out;

}
