/**
 * Orzapad tab setup
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Network/Manager.h>

#include <Widget/BaseLineEdit.h>

#include <ui_PiTab.h>

/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App {

/**
 * Forwarding
 */


/**
 * Main class
 */

class PadTab : public QWidget {

	Q_OBJECT;

	public:

		PadTab( MainWindow * );


	private:

		/**
		 * Fullscreen flag
		 */

		MainWindow * _App;

};

} };
