/**
 * Pi layout
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Audio/Port.h>

#include <ui_ControlPort.h>

/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

class ControlPort : public QWidget {

    Q_OBJECT;

    public:

        ControlPort( Audio::Port * );


    public slots:

        void addControlPortValue();

    private:

        Ui_ControlPort _UI;

        QWidget * _WidgetContent;

};

} } };
