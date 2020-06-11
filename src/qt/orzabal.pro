#-------------------------------------------------
#
# Project created by QtCreator 2016-10-25T20:24:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-creator-test
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui \
    UI/About.ui \
    Pi/PiTab.ui \
    Widget/PatchBay.ui \
    Widget/PatchBayItem.ui \
    Widget/SingleInstrument.ui \
    MidiControl/Control.ui \
    MidiControl/ControlPort.ui \
    MidiControl/ControlPortValue.ui \
    LV2/PluginArea.ui

DISTFILES += \
    About.ui.qml \
    About.qml
