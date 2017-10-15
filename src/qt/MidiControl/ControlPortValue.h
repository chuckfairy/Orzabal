/**
 * Pi layout
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Audio/Port.h>

#include <ui_ControlPortValue.h>


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

class ControlPortValue : public QWidget {

    Q_OBJECT;

    public:

        ControlPortValue( Audio::Port *, Audio::Port * effectPort );

        void setRange( float start, float end );

    public slots:

    private:

        Ui_ControlPortValue _UI;

        QWidget * _WidgetContent;

        void updateRange();


};

} } };

