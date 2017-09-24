/**
 * Settings layout tab
 */
#include <string>
#include <vector>
#include <iostream>

#include <QtCore>

#include <MainWindow.h>

#include <Layouts/LayoutLoader.h>

#include "Events/OutputChangeEvent.h"
#include "Layout.h"


using std::string;
using std::vector;


namespace Orza { namespace App {  namespace Settings {


/**
 * Construct
 */

Layout::Layout( MainWindow * win ) :
    _App( win ),
    _LayoutWriter( new Orza::App::Layouts::LayoutWriter )
{

    setDropdowns();
    setEvents();
    setAppUI();

};


/**
 * Set dropdown widgets and events
 */

void Layout::setDropdowns() {

    _LeftOutput = new OutputDropdown( _App->getServer() );
    _RightOutput = new OutputDropdown( _App->getServer() );

    _RightOutput->setCurrentIndex( 1 );


     //Settings

    QComboBox * dropdown = _App->getUI()->load_layout_dropdown;

    vector<string> fileNames = _App->getLayoutLoader()->getFileNames();

    vector<string>::const_iterator it;

    for( it = fileNames.begin(); it < fileNames.end(); ++ it ) {

        dropdown->addItem( it->c_str() );

    }

};


void Layout::setEvents() {

    //Output changing

    _Event = (Util::Event*) new OutputChangeEvent( this );

    _LeftOutput->on( OutputDropdown::CHANGE_EVENT, _Event );
    _RightOutput->on( OutputDropdown::CHANGE_EVENT, _Event );


    //Save click

    connect(
        _App->getUI()->save_layout_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleSaveClick() )
    );


    connect(
        _App->getUI()->load_layout_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handlePresetLoadClick() )
    );

};

/**
 * App UI setting
 */

void Layout::setAppUI() {

    _App->getUI()->horizontalLayout_5->addWidget( _LeftOutput );
    _App->getUI()->horizontalLayout_5->addWidget( _RightOutput );

};


/**
 * Save layout
 */

void Layout::saveLayout() {

    std::string layoutName = _App->getUI()
        ->save_layout_input
        ->text()
        .toStdString();

    _LayoutWriter->writeLayoutToFile(
        layoutName,
        _App->getServer()->getPatchbay()
    );

};


/**
 * load preset from dropdown
 */

void Layout::loadPreset() {

    std::string layoutName = _App->getUI()
        ->load_layout_dropdown
        ->currentText()
        .toStdString();

    //_App->getLayoutLoader()->getCurrent()->loadFromName( layoutName.c_str() );

};


/**
 * Qt handler for save click
 */

void Layout::handleSaveClick() {

    saveLayout();

};

void Layout::handlePresetLoadClick() {

    loadPreset();

};


/**
 * Update output ports to selected inputs
 */

void Layout::updateOutputPorts() {

    const int left = _LeftOutput->currentIndex();
    const int right = _RightOutput->currentIndex();

    vector<Jack::Port> ports = _App->getServer()
        ->getAudio()
        ->getInputPorts();

    _App->getServer()
        ->getAudio()
        ->disconnectOutputs();

    _App->getServer()
        ->getAudio()
        ->connectOutputTo(
            ports[ left ].name,
            ports[ right ].name
        );

};

}; }; };
