/**
 * Pi layout
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Audio/Port.h>
#include <Audio/PluginPortContainer.h>

#include <Midi/Control.h>
#include <Jack/Midi.h>

#include <ui_ControlPortValue.h>


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

class ControlPortValue : public QWidget {

    Q_OBJECT;

    public:

        explicit ControlPortValue( Jack::MidiControlPort *, Audio::PluginPortContainer * );

        void setRange( float start, float end );

        QWidget * getWidget() {

            return _WidgetContent;

        };

        static unsigned int PERCISION;


    public slots:

        void handleUpdateRange();


    private:

        /**
         * UI
         */

        Ui_ControlPortValue _UI;

        QWidget * _WidgetContent;


        /**
         * Server ports
         */

        Jack::MidiControlPort * _ControlPort;

        Audio::PluginPortContainer * _PortContainer;

        void updateRange();

        void setValue();

        float fromVal = .0;

        float toVal = .0;

};

} } };

