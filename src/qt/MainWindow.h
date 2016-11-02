/**
 * Main window class
 *
 */
#pragma once

#include <QtCore>
#include "ui_MainWindow.h"
#include "widget/InstrumentDropdown.h"
#include "widget/EffectsList.h"


class MainWindow : public QMainWindow {

    public:

        //  override the constructor
        MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);


        /**
         * Qt Window UI
         */
        Ui_MainWindow UI;


        /**
         * Instrument dropdown
         *
         */
        InstrumentDropdown *dropdown;

        /**
         * Effect dropdown
         *
         */
        EffectsList *effects;

};
