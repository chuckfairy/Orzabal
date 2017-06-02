/**
 * Instrument dropdown / combobox widget
 *
 */
#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <QtCore>
#include <QtGui>
#include <QComboBox>
#include <QMessageBox>

#include <LV2/Search.h>
#include <Audio/Plugin.h>
#include <Util/Dispatcher.h>
#include <Jack/Server.h>

#include "InstrumentOption.h"

using std::vector;


namespace Orza { namespace App { namespace Widget {


/**
 * Instrument dropdown GUI
 *
 */

class AbstractPluginDropdown :
    public QComboBox,
    public Util::Dispatcher
{

    Q_OBJECT


    public:

        AbstractPluginDropdown( QWidget * parent );
        AbstractPluginDropdown( Jack::Server * );
        ~AbstractPluginDropdown() {};


        /**
         * Add instrument append order
         *
         * @param InstrumentOption instrument To be added
         *
         */

        bool addPlugin( InstrumentOption *instrument ) {

            return addPlugin( instrument, -1 );

        };


        /**
         * Add instrument
         * will check for dups
         *
         * @param InstrumentOption instrument To be added
         * @param int order Position to be added
         *
         */

        bool addPlugin( InstrumentOption *instrument, const int order );


    protected:

        /**
         * Instrument struct list
         *
         */
        vector<const InstrumentOption*> _plugins;


        /**
         * Jack server
         */

        Jack::Server * _Server;


        /**
         * Default select something
         *
         */

        InstrumentOption _placeholder { "-- Select Instrument --" };


};

} } };
