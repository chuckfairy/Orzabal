/**
 * Plugin UI
 *
 */
#pragma once

#include <lilv/lilv.h>
#include <suil/suil.h>
#include <sratom/sratom.h>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QScrollArea>

#include <Audio/UIDriver.h>

#include <LV2/UI.h>
#include <LV2/Plugin.h>
#include <LV2/include/types.h>

#include "PresetDropdown.h"


/**
 * Forwarding
 */

namespace LV2 {

class PortContainer;

class Port;

}


namespace Orza { namespace App { namespace LV2UI {


class PresetDropdown;


/**
 * UI use lv2 driver
 *
 */

class UIDriver : public Audio::UIDriver {

    public:

        UIDriver( LV2::UI * );


        /**
         * Virtual loading
         */

        void start();

        void stop();

        void update();

        void resize();


        /**
         * Unique Lilv setups
         */

        void createUI();

        QWidget * createControlWidget();

        bool portGroupLessThan( const LV2::PortContainer &, const LV2::PortContainer & );


        QScrollArea * getWidget() {

            return _MainWidget;

        };


        QWidget* getControlWidget() {

            return _controlWidget;

        };

    protected:

        LV2::UI * _UI;

    private:

        /**
         * Widget object
         */

        QMainWindow * win;

        QScrollArea * _MainWidget;

        QWidget* _controlWidget;

        PresetDropdown * _PresetDropdown;


        /**
         *  Lilv types
         */

        const LilvPlugin * _lilvPlugin;

        LilvWorld * _lilvWorld;

        LilvUIs * _lilvUIS;

        const LilvUI * _lilvUI;

        const LilvNode * _uiType;

};

}; }; };
