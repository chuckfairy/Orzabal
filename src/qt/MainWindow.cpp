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


    //Jack Startup

    _Server = new JackServer();

    _Server->start();

    _Server->connectDefault();


    //Widget creation

    dropdown = new InstrumentDropdown();

    effects = new EffectsList();

    midiDevices = new MidiDeviceDropdown();

    Outputs = new OutputDropdown( _Server );


    //UI creation

    UI.horizontalLayout_4->insertWidget( 0, dropdown );
    UI.horizontalLayout_3->addWidget( effects );
    UI.horizontalLayout_6->addWidget( midiDevices );
    UI.horizontalLayout_5->addWidget( Outputs );

};
