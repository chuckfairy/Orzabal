/**
 * Pi layout
 */
#pragma once

#include <vector>

#include <QtCore>
#include <QWidget>

#include <Util/Repository.h>

#include <Jack/Midi.h>

#include <ui_Control.h>

#include <Widget/TreeNode.h>

#include "ControlPort.h"


using std::vector;

using Jack::MidiControlPort;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace MidiControl {


/**
 * Main class
 */

class Control : public Widget::TreeNode {

    Q_OBJECT;

    public:

        Control( MainWindow * );

        /**
         * Main getter
         */

        QWidget * getWidget() {

            return _WidgetContent;

        };


    public slots:

        void addControlPort();


    private:

        /**
         * Fullscreen flag
         */

        MainWindow * _App;

        Ui_Control _UI;

        QWidget * _WidgetContent;


        /**
         * Dropdown and midi control ports
         */

        vector<Jack::MidiControlPort*> _Ports;

        void updateDropdown();

};

} } };
