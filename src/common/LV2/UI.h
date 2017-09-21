/**
 * Plugin UI
 *
 */
#pragma once

#include <lilv/lilv.h>
#include <suil/suil.h>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QScrollArea>

#include <Audio/UI.h>
#include <Audio/UIDriver.h>

#include "include/types.h"


namespace LV2 {


/**
 * Forwarding
 *
 */

class Plugin;

class PortContainer;

class Port;

class PresetDropdown;


/**
 * UI use of lilv
 *
 */

class UI : public Audio::UI {

    private:


    protected:


        /**
         *  Overwrite to LV2 member
         */

        LV2::Plugin * _Plugin;

        static Port * portBySymbol( Plugin *, const char * );


    public:

        UI( Plugin * );


        /**
         * Virtual loading
         */

        void start();

        void stop();

        void update();

        void resize();


        /**
         * Default drivers to load
         */

        static vector<Audio::UIDriver*> DefaultDrivers;


        /**
         * Unique Lilv setups
         */

        void createUI();

        void createQt();

        void createNativeUI();

        QWidget * createControlWidget();

        bool portGroupLessThan( const PortContainer &p1, const PortContainer &p2 );


        /**
         * LV2 plugin overwrite
         */

        Plugin * getPlugin();

};

};
