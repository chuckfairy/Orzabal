/**
 * Pi layout
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Audio/Port.h>

#include <Midi/Control.h>
#include <Jack/Midi.h>

#include <ui_ControlPort.h>

#include "ControlPortValue.h"


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

        ControlPort( MainWindow *, Jack::MidiControlPort * );


        /**
         * Getters
         */

        QWidget * getWidget() {

            return _WidgetContent;

        };


    public slots:

        void addControlPortValue();


    private:

        /**
         * Internal
         */

        MainWindow * _App;

        Ui_ControlPort _UI;

        QWidget * _WidgetContent;

        Jack::MidiControlPort * _ControlPort;

        /**
         * Port value and dropdown
         * @TODO remove double vector
         */

        vector<Audio::Plugin*> _Plugins;

        vector<Audio::Port*> _ControlPorts;

        vector<ControlPortValue*> _UIPortValues;

        void updateDropdown();

};

} } };
