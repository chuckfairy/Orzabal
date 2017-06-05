/**
 * Test
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <Audio/Plugin.h>

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

class PatchbayPlugin : public QWidget {

    Q_OBJECT;

    public:

        explicit PatchbayPlugin( Audio::Plugin * );
        explicit PatchbayPlugin();


        /**
         * Getters
         */

        QWidget * getWidget() {

            return _WidgetContent;

        };


    public slots:

        void handleSelectChange( int index );

        void handleRemoveClick();


    private:

        Audio::Plugin * _Plugin;

        QWidget * _WidgetContent;

        Ui_PatchBayItem _UI;

};

} } };
