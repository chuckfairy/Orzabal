/**
 * Test
 */
#pragma once

#include <vector>

#include <QtCore>
#include <QWidget>

#include <ui_PatchBay.h>

#include "EffectDropdown.h"


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

        void removePlugin( PatchbayPlugin * );

        void clearPlugins();

        void addPlugin( Audio::Plugin * );


    public slots:

        void handleAddClick();

        void handleRemoveClick( PatchbayPlugin * );


    private:

        MainWindow * _App;

        QWidget * _WidgetContent;

        EffectDropdown * _Dropdown;

        Ui_PatchBay _UI;

        QLayout * _Layout;

        QWidget * _LayoutWidget;

        vector<PatchbayPlugin*> _plugins;


};

} } };
