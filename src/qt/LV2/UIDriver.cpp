/**
 * UI Drive impl
 */
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

#include "PresetDropdown.h"
#include "WindowLayout.h"
#include "WindowLayout.h"

#include "UIDriver.h"
#include "WindowLayout.h"

#include <LV2/Port.h>
#include <LV2/Plugin.h>


namespace Orza { namespace App { namespace LV2UI {

/**
 * construct
 */

UIDriver::UIDriver( LV2::UI * ui ) :
    _UI( ui )
{

    _PresetDropdown = new PresetDropdown( ui->getPlugin() );

};


/**
 * Construct start setup ports and router
 *
 */

void UIDriver::start() {

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

};


/**
 * Instaniate instances
 */

void UIDriver::createUI() {

    _controlWidget = createControlWidget();

};


/**
 * Create control widget inside main
 */

QWidget * UIDriver::createControlWidget() {

	QList<LV2::PortContainer> portContainers;

    LV2::Plugin * _Plugin = _UI->getPlugin();

    int numPorts = _Plugin->getNumPorts();

    for( int i = 0; i < _Plugin->getNumPorts(); ++ i ) {

        LV2::Port * port = (LV2::Port*)_Plugin->getPort( i );

		if( port->type != Audio::TYPE_CONTROL ) { continue; }

        LV2::PortContainer portContainer;
        portContainer.ui = _UI;
        portContainer.port = port;
        portContainers.append( portContainer );

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
    dropdownLayout->addWidget( _PresetDropdown );

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

    for (int i = 0; i < portContainers.count(); ++i) {

        LV2::PortContainer portContainer = portContainers[i];
        LV2::Port* port = portContainer.port;

        Control *  control = new Control( portContainer );

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


}; }; };
