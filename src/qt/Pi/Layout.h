/**
 * Pi layout
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


namespace Orza { namespace App { namespace Pi {

/**
 * Forwarding
 */


/**
 * Main class
 */

class Layout : public QWidget {

    Q_OBJECT;

    public:

        Layout( MainWindow * );


        /**
         * Fullscreen Getter
         */

        bool isFullscreen() {

            return FULLSCREEN;

        };


        /**
         * Hardware commands
         */

        void shutdown();

        void restart();


    public slots:

        /**
         * Window actions
         */

        void goFullscreen();

        void goWindowed();


        /**
         * Main toggle method
         */

        void toggleFullscreen();


        /**
         * Hardware command slots
         */

        void handleShutdown();

        void handleRestart();


    private:

        /**
         * Fullscreen flag
         */

        bool FULLSCREEN = false;

        MainWindow * _App;

        Ui_PiTab _Tab;

        QWidget * _WidgetContent;

        /**
         * Widgets
         */

        Widget::BaseLineEdit * _WifiPass;


        /**
         * Network
         */

        Network::Manager * _Manager;

        void setNetworkManager();


    private slots:

        void updateNetworks();

        void connectNetwork();

};

} } };
