/**
 * Outer window
 *
 */
#include <QHBoxLayout>
#include "MainWindow.h"
#include "widget/EffectsList.h"
#include "Settings/MidiDeviceDropdown.h"

/**
 * Window construct
 *
 * @Override
 */
MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {

    UI.setupUi( this );

    dropdown = new InstrumentDropdown();

    effects = new EffectsList();

    midiDevices = new MidiDeviceDropdown();

    UI.horizontalLayout_4->insertWidget( 0, dropdown );
    UI.horizontalLayout_3->addWidget( effects );
    UI.horizontalLayout_6->addWidget( midiDevices );

};
