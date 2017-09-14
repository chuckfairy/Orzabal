/**
 * Plugin UI
 *
 */
#include <jack/jack.h>
#include <jack/midiport.h>

#include <lilv/lilv.h>
#include <suil/suil.h>

#include <QWindow>
#include <QGuiApplication>
#include <QApplication>
#include <QScrollArea>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QStyle>
#include <QPushButton>
#include <QDial>
#include <QLabel>

#include "Port.h"
#include "UI/PresetDropdown.h"
#include "UI.h"
#include "Plugin.h"


namespace LV2 {


/**
 * construct
 */

UI::UI( Plugin * p ) {

    setPlugin( p );

};


/**
 * Construct start setup ports and router
 *
 */

void UI::start() {

    startDrivers();

};


/**
 *
 */

void UI::stop() {

    stopDrivers();

};


/**
 * UI gui updating
 * called from timer
 *
 */

void UI::update() {

    updateDrivers();

};

};
