/**
 * Pi layout
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <ui_Control.h>

/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace MidiControl {

/**
 * Forwarding
 */


/**
 * Main class
 */

class Control : public QWidget {

    Q_OBJECT;

    public:

        Control( MainWindow * );


    public slots:

        void addControlPort();

    private:

        /**
         * Fullscreen flag
         */

        bool FULLSCREEN = false;

        MainWindow * _App;

        Ui_Control _UI;

        QWidget * _WidgetContent;

};

} } };

