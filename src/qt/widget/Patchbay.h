/**
 * Test
 */
#pragma once

#include <vector>

#include <QtCore>
#include <QWidget>

#include <ui_PatchBay.h>

using std::vector;


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Widget {

class PatchbayPlugin;


/**
 * Main class
 */

class Patchbay : public QWidget {

    Q_OBJECT;

    public:

        Patchbay( MainWindow * );


        /**
         * Add action
         */

        void addPlugin();

        void movePlugin();

        void removePlugin();


    public slots:

        void handleAddClick();

        void handleRemoveClick( bool );

    private:

        MainWindow * _App;

        QWidget * _WidgetContent;

        Ui_PatchBay _UI;

        QLayout * _Layout;

        QWidget * _LayoutWidget;

        vector<PatchbayPlugin*> _plugins;


};

} } };
