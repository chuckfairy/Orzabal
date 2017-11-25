/**
 * UI Drive impl
 */
#include <vector>

#include <jack/jack.h>
#include <jack/midiport.h>

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

#include <Widget/InputDropdown.h>
#include <Widget/OutputDropdown.h>

#include "PresetDropdown.h"
#include "WindowLayout.h"
#include "WindowLayout.h"

#include "PortContainer.h"
#include "UIDriver.h"
#include "WindowLayout.h"

#include <Audio/Plugin.h>

#include <LV2/Port.h>
#include <LV2/Plugin.h>

using std::vector;

namespace Orza { namespace App { namespace LV2UI {

/**
 * construct
 */

UIDriver::UIDriver( Jack::Server * s, LV2::UI * ui ) :
    _Server( s ),
    _UI( ui ),
    _pluginAreaWidget( new QWidget )
{

    //Setup area

    _UIArea.setupUi( _pluginAreaWidget );



    //Setup preset dropdown

    _PresetDropdown = new PresetDropdown( ui->getPlugin() );

    _UIArea.preset_layout->addWidget( _PresetDropdown );


    //Start if active

    if ( _UI->getPlugin()->isActive() ) {

        start();

    }

};


/**
 * Construct start setup ports and router
 *
 */

void UIDriver::start() {

    setupInputPorts();

    setupOutputPorts();

    setupMidiPorts();

    createUI();

};


/**
 *
 */

void UIDriver::stop() {

};


/**
 * UI gui updating
 * called from timer
 *
 */

void UIDriver::update() {

    //Check ports

    Audio::Plugin * p = _UI->getPlugin();

    for( int i = 0; i < portContainer.size(); ++ i ) {

        updatePort( portContainer[ i ] );

    }

};


/**
 * Update port check if change
 */

void UIDriver::updatePort( PortContainer container ) {

    if( container.port->control != container.controlWidget->getValue() ) {

        container.controlWidget->setValue( container.port->control );

    }

};


/**
 * Instaniate instances
 */

void UIDriver::createUI() {

    _controlWidget = createControlWidget();

    _controlWidget->setSizePolicy(
        QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding )
    );

    _UIArea.verticalLayout->addWidget( _controlWidget );

};


/**
 * Create control widget inside main
 */

QWidget * UIDriver::createControlWidget() {

    LV2::Plugin * _Plugin = _UI->getPlugin();

    int numPorts = _Plugin->getNumPorts();

    for( int i = 0; i < _Plugin->getNumPorts(); ++ i ) {

        LV2::Port * port = (LV2::Port*)_Plugin->getPort( i );

		if( port->type != Audio::TYPE_CONTROL ) { continue; }

        PortContainer container;
        container.ui = _UI;
        container.port = port;
        portContainer.push_back( container );

    }

    //Main layout
    QLayout * fullLayout = new QVBoxLayout;
    QWidget * fullWidget = new QWidget;


    //Grid layout for controls
    QWidget* grid = new QWidget();
    FlowLayout* flowLayout = new FlowLayout();
    QLayout * layout = flowLayout;


    //Add dropdown

    _PresetDropdown->load();

    QHBoxLayout * dropdownLayout = new QHBoxLayout;


    //Add items
    fullLayout->addItem( dropdownLayout );
    fullLayout->addItem( layout );


    //Create knobs for controls

    LilvNode * lastGroup = NULL;
    QHBoxLayout * groupLayout;

    const LilvPlugin * _lilvPlugin = _Plugin->getLilvPlugin();
    LilvWorld * _lilvWorld = _Plugin->getLilvWorld();

    LilvNode * pg_group = lilv_new_uri( _lilvWorld, LV2_PORT_GROUPS__group);
    LilvNode * lv2_name = lilv_new_uri( _lilvWorld, LV2_CORE__name );
    LilvNode* pprop_notOnGUI = lilv_new_uri( _lilvWorld, LV2_PORT_PROPS__notOnGUI );

    for (int i = 0; i < portContainer.size(); ++i) {

        PortContainer * container = &portContainer[i];
        LV2::Port * port = container->port;

        Control *  control = new Control( *container );

        container->controlWidget = control;

        LilvNode* group = lilv_port_get(
            _lilvPlugin,
            port->lilv_port,
            pg_group
        );

        if( group ) {

            if (!lilv_node_equals(group, lastGroup)) {

                /* Group has changed */

                LilvNode* groupName = lilv_world_get( _lilvWorld, group, lv2_name, NULL );

                QGroupBox* groupBox = new QGroupBox(lilv_node_as_string(groupName));

                groupLayout = new QHBoxLayout();
                groupBox->setLayout(groupLayout);
                layout->addWidget(groupBox);

            }

            groupLayout->addWidget( control );

        } else {

            layout->addWidget( (QGroupBox*) control );

        }

        lastGroup = group;

        uint32_t index = lilv_port_get_index( _lilvPlugin, port->lilv_port );

        port->widget = control;

    }

    fullWidget->setLayout( fullLayout );

    lilv_node_free( pprop_notOnGUI );

    return fullWidget;

};


/**
 * Port group boxes setup
 */

void UIDriver::setupInputPorts() {

    Audio::Plugin * p = (Audio::Plugin*) _UI->getPlugin();

    if( ! p->hasInputs() ) {

        _UIArea.input_groupbox->hide();

        return;

    }


    //Setup dropdowns

    vector<long> * inputs = p->getInputPorts();
    vector<long>::iterator it;

    for( it = inputs->begin(); it != inputs->end(); ++ it ) {

        Audio::Port * port = p->getPort( (*it) );

        QLabel * label = new QLabel;

        label->setText( port->nameString.c_str() );

        _UIArea.input_layout->addWidget( label );

        InputDropdown * dropdown = new InputDropdown( _Server );

        _UIArea.input_layout->addWidget( dropdown );

    }

};

void UIDriver::setupOutputPorts() {

    Audio::Plugin * p = (Audio::Plugin*) _UI->getPlugin();

    if( ! p->hasOutputs() ) {

        _UIArea.output_groupbox->hide();

        return;

    }


    //Setup dropdowns

    vector<long> * outputs = p->getOutputPorts();
    vector<long>::iterator it;

    for( it = outputs->begin(); it != outputs->end(); ++ it ) {

        Audio::Port * port = p->getPort( (*it) );

        QLabel * label = new QLabel;

        label->setText( port->nameString.c_str() );

        _UIArea.output_layout->addWidget( label );

        OutputDropdown * dropdown = new OutputDropdown( _Server );

        _UIArea.output_layout->addWidget( dropdown );

    }

};

void UIDriver::setupMidiPorts() {

    Audio::Plugin * p = (Audio::Plugin*) _UI->getPlugin();

    if( ! p->hasMidi() ) {

        _UIArea.midi_groupbox->hide();

        return;

    }

};

}; }; };
