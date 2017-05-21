/**
 * Test
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <ui_PatchBay.h>


/**
 * Forwarding
 */

class MainWindow;


namespace Orza { namespace App { namespace Widget {

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

        void handleAddClick( int index );

        void handleRemoveClick( int index );

    private:

        MainWindow * _App;

        QWidget * _WidgetContent;

        Ui_PatchBay _UI;


};

} } };
