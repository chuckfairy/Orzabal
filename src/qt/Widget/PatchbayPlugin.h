/**
 * Test
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Audio/Plugin.h>
#include <Util/Dispatcher.h>

#include <Jack/Server.h>

#include <ui_PatchBayItem.h>


/**
 * Forwarding
 */

class MainWindow;

namespace LV2 {

    class Plugin;

};


namespace Orza { namespace App { namespace Widget {

/**
 * Main class
 */

class PatchbayPlugin : public QWidget, public Util::Dispatcher {

    Q_OBJECT;

    public:

        explicit PatchbayPlugin( Jack::Server *, Audio::Plugin * const );
        explicit PatchbayPlugin();

        ~PatchbayPlugin();


        /**
         * Getters
         */

        QWidget * getWidget() {

            return _WidgetContent;

        };


        /**
         * Event
         */

        static const char * REMOVE_EVENT;

        static const char * ACTIVATE_EVENT;


        /**
         * Active related
         */

        void setActive();

        void setInactive();

        void toggleActive();


    public slots:

        void handleViewClick();

        void handleActiveClick();

        void handleRemoveClick();


        /**
         * Getters
         */

        Ui_PatchBayItem * getUI() {

            return &_UI;

        };

        Audio::Plugin * getPlugin() {

            return _Plugin;

        };


    private:

        /**
         * Main obj
         */

        Jack::Server * _Server;

        Audio::Plugin * _Plugin;

        QWidget * _WidgetContent;

        Ui_PatchBayItem _UI;

};

} } };
