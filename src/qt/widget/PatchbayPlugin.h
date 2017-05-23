/**
 * Test
 */
#pragma once

#include <QtCore>
#include <QWidget>

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

        PatchbayPlugin( LV2::Plugin * );
        PatchbayPlugin();


    public slots:

        void handleSelectChange( int index );

        void handleRemoveClick();


    private:

        LV2::Plugin * _Plugin;

        QWidget * _WidgetContent;

        Ui_PatchBayItem _UI;

};

} } };
