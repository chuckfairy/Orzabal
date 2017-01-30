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
#include <QDial>
#include <QLabel>

#include "UI.h"
#include "Plugin.h"
#include "WindowLayout.h"


namespace LV2 {


/**
 * construct
 */

UI::UI( Plugin * p ) {

    setPlugin( p );

    setLilvPlugin( p->getLilvPlugin() );

    setLilvWorld( p->getLilvWorld() );

    setLilvInstance( p->getLilvInstance() );

};


/**
 * Construct start setup ports and router
 *
 */

void UI::start() {

    // Get a plugin UI

    _lilvUIS = lilv_plugin_get_uis( _lilvPlugin );

    const LilvNode* native_ui_type = lilv_new_uri( _lilvWorld, _NATIVE_UI_TYPE );

    LILV_FOREACH(uis, u, _lilvUIS) {

        const LilvUI* this_ui = lilv_uis_get( _lilvUIS, u );

        if( lilv_ui_is_supported( this_ui, suil_ui_supported, native_ui_type, &_uiType ) ) {
            /* TODO: Multiple UI support */
            _lilvUI = this_ui;
            break;
        }

    }

    //} else {

    //} REMOVE

    //_lilvUI = lilv_uis_get( _lilvUIS, lilv_uis_begin( _lilvUIS ) );

    if( ! _lilvUI ) {

        LILV_FOREACH( uis, u, _lilvUI ) {

            const LilvUI* ui = lilv_uis_get( _lilvUIS, u );

            const LilvNodes* types = lilv_ui_get_classes(ui);

            LILV_FOREACH( nodes, t, types ) {

                const char * pt = lilv_node_as_uri( lilv_nodes_get( types, t ) );

                if (!strcmp(pt, "http://kxstudio.sf.net/ns/lv2ext/external-ui#Widget")) {

                    _EXTERNAL_UI = true;
                    _lilvUI = ui;
                    _uiType = getExternalKX();

                } else if ( ! strcmp( pt, "http://lv2plug.in/ns/extensions/ui#external" ) ) {

                    _EXTERNAL_UI = true;
                    _lilvUI = ui;
                    _uiType = getExternalLV2();

                }

            }

        }

    }


    /* Create ringbuffers for UI if necessary */

    if( _lilvUI ) {

        fprintf(stderr, "UI: %s\n", lilv_node_as_uri( lilv_ui_get_uri( _lilvUI ) ) );
        fprintf(stderr, "UI Type: %s\n", lilv_node_as_uri( _uiType ) );

    } else {

        fprintf(stderr, "UI: None\n");

    }


    //Create jack ring buffers @TODO move to plugin grab

    //_uiPortEvents = jack_ringbuffer_create( 4096 );

    createUI();

};


/**
 *
 */

void UI::stop() {

    suil_host_free( _uiSuil );
    sratom_free( _uiSratom );
    lilv_uis_free( _lilvUIS );
    free( _uiEventBuf );

};


/**
 * UI gui updating
 * called from timer
 *
 */

void UI::update() {

	/* Emit UI events. */
//    ControlChange ev;
//    const size_t  space = jack_ringbuffer_read_space(jalv->plugin_events);
//    for(
//        size_t i = 0;
//        i + sizeof(ev) + sizeof(float) <= space;
//        i += sizeof(ev) + ev.size
//    ) {
//        //Read event header to get the size
//        jack_ringbuffer_read( plugin_events, (char*)&ev, sizeof(ev));
//
//        //Resize read buffer if necessary
//        _uiEventBuf = realloc( _uiEventBuf, ev.size );
//        void* const buf = _uiEventBuf;
//
//        //Read event body
//        jack_ringbuffer_read( plugin_events, buf, ev.size );
//
//        if( jalv->opts.dump && ev.protocol == atom_eventTransfer ) {
//
//            //Dump event in Turtle to the console
//            LV2_Atom* atom = (LV2_Atom*)buf;
//            char * str  = sratom_to_turtle(
//                jalv->ui_sratom, &jalv->unmap, "jalv:", NULL, NULL,
//                atom->type, atom->size, LV2_ATOM_BODY(atom)
//            );
//
//            //jalv_ansi_start(stdout, 35);
//            //printf("\n## Plugin => UI (%u bytes) ##\n%s\n", atom->size, str);
//            //jalv_ansi_reset(stdout);
//            free(str);
//
//        }
//
//        if ( _lilvUI ) {
//
//            suil_instance_port_event(
//                _lilvUI,
//                ev.index,
//                ev.size, ev.protocol, buf
//            );
//
//        } else {
//
//            jalv_ui_port_event(jalv, ev.index, ev.size, ev.protocol, buf);
//
//        }
//
//        if (ev.protocol == 0 && jalv->opts.print_controls) {
//            //print_control_value(jalv, &jalv->ports[ev.index], *(float*)buf);
//        }
//
//    }
//
//    if (jalv->externalui && jalv->extuiptr) {
//        LV2_EXTERNAL_UI_RUN(jalv->extuiptr);
//    }

};


/**
 * Instaniate instances
 */

void UI::createUI() {

    win = new QMainWindow();

    if( ! _lilvUI ) {

        createQt();

    } else {

        createNativeUI();

    }

}

void UI::createNativeUI() {

    _uiSuil = suil_host_new( UI::suilUIWrite, UI::suilPortIndex, NULL, NULL);

    const LV2_Feature parent_feature = {
        LV2_UI__parent, win
    };

    const LV2_Feature instance_feature = {
        NS_EXT "instance-access", lilv_instance_get_handle( _lilvInstance )
    };

    const LV2_Feature data_feature = {
        LV2_DATA_ACCESS_URI, &ext_data
    };

    const LV2_Feature idle_feature = {
        LV2_UI__idleInterface, NULL
    };

    const LV2_Feature* ui_features[] = {
        &uri_map_feature, &map_feature, &unmap_feature,
        &instance_feature,
        &data_feature,
        &log_feature,
        &parent_feature,
        &options_feature,
        &idle_feature,
        NULL
    };

    extuiptr = NULL;

    const char* bundle_uri = lilv_node_as_uri( lilv_ui_get_bundle_uri( _lilvUI ) );
    const char* binary_uri = lilv_node_as_uri( lilv_ui_get_binary_uri( _lilvUI ) );

    char* bundle_path = lilv_file_uri_parse( bundle_uri, NULL );
    char* binary_path = lilv_file_uri_parse( binary_uri, NULL );

    if( _EXTERNAL_UI ) {

        const LV2_Feature external_lv_feature = {
            LV2_EXTERNAL_UI_DEPRECATED_URI, win
        };

        const LV2_Feature external_kx_feature = {
            LV2_EXTERNAL_UI__Host, win
        };

        const LV2_Feature parent_feature = {
            LV2_UI__parent, win
        };

        const LV2_Feature instance_feature = {
            NS_EXT "instance-access", lilv_instance_get_handle( _lilvInstance )
        };

        const LV2_Feature data_feature = {
            LV2_DATA_ACCESS_URI, &ext_data
        };

        const LV2_Feature* ui_features[] = {
            &uri_map_feature, &map_feature, &unmap_feature,
            &instance_feature,
            &data_feature,
            &log_feature,
            &external_lv_feature,
            &external_kx_feature,
            &parent_feature,
            &options_feature,
            NULL
        };

        return;

        _uiInstance = suil_instance_new(
            _uiSuil,
            this,
            _NATIVE_UI_TYPE,
            lilv_node_as_uri( lilv_plugin_get_uri( _lilvPlugin ) ),
            lilv_node_as_uri( lilv_ui_get_uri( _lilvUI ) ),
            lilv_node_as_uri( _uiType ),
            bundle_path,
            binary_path,
            ui_features
        );

        if( _uiInstance ) {

            extuiptr = suil_instance_get_widget((SuilInstance*) _uiInstance );

        } else {

            _EXTERNAL_UI = false;

        }

    } else {

        const LV2_Feature parent_feature = {
            LV2_UI__parent, win
        };

        const LV2_Feature instance_feature = {
            NS_EXT "instance-access", lilv_instance_get_handle( _lilvInstance )
        };

        const LV2_Feature data_feature = {
            LV2_DATA_ACCESS_URI, &ext_data
        };

        const LV2_Feature* ui_features[] = {
            &uri_map_feature, &map_feature, &unmap_feature,
            &instance_feature,
            &data_feature,
            &log_feature,
            &parent_feature,
            &options_feature,
            NULL
        };

        const char * p = lilv_node_as_uri( lilv_plugin_get_uri( _lilvPlugin ) );
        const char * ui  = lilv_node_as_uri( lilv_ui_get_uri( _lilvUI ) );
        const char * t = lilv_node_as_uri( _uiType );

        return;

        _uiInstance = suil_instance_new(
            _uiSuil,
            this,
            _NATIVE_UI_TYPE,
            p,
            ui,
            t,
            bundle_path,
            binary_path,
            ui_features
        );

    }

    lilv_free(binary_path);
    lilv_free(bundle_path);

    /* Set initial control values on UI */
    if ( _uiInstance ) {

        for (uint32_t i = 0; i < _Plugin->getNumPorts(); ++i) {

            Port * port = (Port*) _Plugin->getPort( i );

            if( port->type  == Audio::TYPE_CONTROL) {

                suil_instance_port_event( _uiInstance, i,
                    sizeof(float), 0,
                    &port->type
                );
            }

        }

    }

};

void UI::createQt() {

	_MainWidget = new QScrollArea();

    QWidget* controlWidget = createControlWidget();

    ((QScrollArea*)_MainWidget)->setWidget(controlWidget);

    ((QScrollArea*)_MainWidget)->setWidgetResizable(true);

    _MainWidget->setMinimumWidth(800);

    _MainWidget->setMinimumHeight(600);

};

QWidget * UI::createControlWidget() {

	QList<PortContainer> portContainers;

    int numPorts = _Plugin->getNumPorts();

    for( int i = 0; i < _Plugin->getNumPorts(); i ++ ) {

        Port * port = (Port*)_Plugin->getPort( i );

		if( port->type == Audio::TYPE_CONTROL ) {

            PortContainer portContainer;
            portContainer.ui = this;
            portContainer.port = port;
            portContainers.append( portContainer );

        }

    }

    QWidget* grid = new QWidget();
    FlowLayout* flowLayout = new FlowLayout();
    QLayout* layout = flowLayout;

    LilvNode * lastGroup = NULL;
    QHBoxLayout * groupLayout;

    LilvNode * pg_group = lilv_new_uri( _lilvWorld, LV2_PORT_GROUPS__group);
    LilvNode * lv2_name = lilv_new_uri( _lilvWorld, LV2_CORE__name );
    LilvNode* pprop_notOnGUI = lilv_new_uri( _lilvWorld, LV2_PORT_PROPS__notOnGUI );


    for (int i = 0; i < portContainers.count(); ++i) {

        PortContainer portContainer = portContainers[i];
        Port* port = portContainer.port;

        Control*  control = new Control( portContainer );
        LilvNode* group = lilv_port_get( _lilvPlugin, port->lilv_port, pg_group );

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

    grid->setLayout(layout);

    lilv_node_free(pprop_notOnGUI);

    return grid;

};


/**
 * UI is resiable node find
 */

bool UI::isResizeable( UI * ui ) {

    return ui->hasResize();

};


/**
 * UI has resize opt
 */

bool UI::hasResize() {

    const LilvNode * s = lilv_ui_get_uri( _lilvUI );
    LilvNode * p = lilv_new_uri( _lilvWorld, LV2_CORE__optionalFeature);
    LilvNode * fs = lilv_new_uri( _lilvWorld, LV2_UI__fixedSize);
    LilvNode * nrs = lilv_new_uri( _lilvWorld, LV2_UI__noUserResize);

    LilvNodes * fs_matches = lilv_world_find_nodes( _lilvWorld, s, p, fs );
    LilvNodes * nrs_matches = lilv_world_find_nodes( _lilvWorld, s, p, nrs );

    lilv_nodes_free( nrs_matches );
    lilv_nodes_free( fs_matches );
    lilv_node_free( nrs );
    lilv_node_free( fs );
    lilv_node_free( p );

    return !fs_matches && !nrs_matches;

};


/**
 * External kx studio plugin URI
 *
 */

LilvNode * UI::getExternalKX() {

    return lilv_new_uri( _Plugin->getLilvWorld(), "http://kxstudio.sf.net/ns/lv2ext/external-ui#Widget" );

};


/**
 * External lv studio plugin URI
 *
 */

LilvNode * UI::getExternalLV2() {

    return lilv_new_uri( _Plugin->getLilvWorld(), "http://lv2plug.in/ns/extensions/ui#external" );

};


/**
 * Port get by symbol
 */

Port * UI::portBySymbol( Plugin * p, const char * sym ) {

    for ( uint32_t i = 0; i < p->getNumPorts(); ++ i ) {

        Port * port = (Port*) p->getPort( i );

        const LilvNode* port_sym = lilv_port_get_symbol( p->getLilvPlugin(), port->lilv_port );

        if( ! strcmp( lilv_node_as_string( port_sym ), sym ) ) {

            return port;

        }

    }

    return NULL;

};


/**
 * Suil UI writing
 */

void UI::suilUIWrite(
    SuilController controller,
    uint32_t port_index,
    uint32_t buffer_size,
    uint32_t protocol,
    const void * buffer
) {

};


/**
 * Port returning
 */

uint32_t UI::suilPortIndex( SuilController controller, const char * symbol ) {

    Plugin * p = (Plugin*)controller;

    Port * port = UI::portBySymbol( p, symbol );

    return port ? port->index : LV2UI_INVALID_PORT_INDEX;

};

};
