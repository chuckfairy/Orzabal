/**
 * Main window class
 *
 */
#pragma once

#include <QtCore>
#include "ui_MainWindow.h"
#include "widget/InstrumentDropdown.h"


class MainWindow : public QMainWindow {

    public:

        //  override the constructor
        MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);

        Ui_MainWindow UI;

        /**
         * Instrument dropdown
         *
         */
        InstrumentDropdown *dropdown;

};
