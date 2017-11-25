/**
 * IO Port changer ui
 */
#pragma once

#include <jack/jack.h>

#include <QtCore>
#include <QtGui>

#include <Jack/Server.h>
#include <Jack/Port.h>

namespace Orza { namespace App { namespace LV2UI {

class IOPortChanger {

    public:

        explicit IOPortChanger( Jack::Server *, Jack::Port * );


        /**
         * Main widget getter
         */

        QWidget * getWidget() {

            return _MainWidget;

        };


    public slots:

        void handleSelectionChanged();


    private:

        Jack::Server * _Server;

        Jack::Port * _port;

        QComboBox * _Dropdown;

        QWidget * _MainWidget;


        /**
         * Create UI
         */

        void createUI();


        /**
         * Main connect
         */

        void connect();

};


}; }; };
