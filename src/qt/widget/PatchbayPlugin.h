/**
 * Test
 */
#pragma once

#include <QtCore>
#include <QWidget>


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

        PatchbayPlugin( Plugin * );


    public slots:

        void handleAddClick( int index );

        void handleRemoveClick( int index );


    private:

        LV2::Plugin * _Plugin;

};

} } };
