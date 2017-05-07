/**
 *
 */
#include <LV2/UI.h>
#include <LV2/UI.h>
#include "NativeUIDriver.h"

namespace LV2 { namespace UIs {

NativeUIDriver::NativeUIDriver() {};


/**
 * Construct start setup ports and router
 *
 */

void NativeUIDriver::start() {

    // Get a plugin UI

    _lilvUIS = lilv_plugin_get_uis( _UI->getLilvPlugin() );

    setNativeUIData();

    //Create jack ring buffers @TODO move to plugin grab

    _uiPortEvents = jack_ringbuffer_create( 4096 );
	jack_ringbuffer_mlock( _uiPortEvents );

    createUI();

};


/**
 * Stop UI / take down
 */

void NativeUIDriver::stop() {

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

void NativeUIDriver::update() {

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
 * Native ui methods
 */

void NativeUIDriver::setNativeUIData() {

    const LilvNode* native_ui_type = lilv_new_uri(
        _UI->getLilvWorld(),
        _NATIVE_UI_TYPE
    );

    LILV_FOREACH(uis, u, _lilvUIS) {

        const LilvUI* this_ui = lilv_uis_get( _lilvUIS, u );

        if( lilv_ui_is_supported( this_ui, suil_ui_supported, native_ui_type, &_uiType ) ) {
            /* TODO: Multiple UI support */
            _lilvUI = this_ui;
            _HAS_LILV_UI = true;
            break;
        }

    }

    //} REMOVE

    //_lilvUI = lilv_uis_get( _lilvUIS, lilv_uis_begin( _lilvUIS ) );

    if( ! _HAS_LILV_UI ) {

        LILV_FOREACH( uis, u, _lilvUIS ) {

            const LilvUI* ui = lilv_uis_get( _lilvUIS, u );

            const LilvNodes* types = lilv_ui_get_classes(ui);

            LILV_FOREACH( nodes, t, types ) {

                const char * pt = lilv_node_as_uri( lilv_nodes_get( types, t ) );

                if (!strcmp(pt, "http://kxstudio.sf.net/ns/lv2ext/external-ui#Widget")) {

                    _HAS_EXTERNAL_UI = true;
                    _lilvUI = ui;
                    _uiType = getExternalKX();

                } else if ( ! strcmp( pt, _LV2_UI_EXTERNAL ) ) {

                    _HAS_EXTERNAL_UI = true;
                    _lilvUI = ui;
                    _uiType = getExternalLV2();

                }

            }

        }

    }


    /* Create ringbuffers for UI if necessary */

    if( _lilvUI ) {

        //fprintf(stderr, "UI: %s\n", lilv_node_as_uri( lilv_ui_get_uri( _lilvUI ) ) );
        //fprintf(stderr, "UI Type: %s\n", lilv_node_as_uri( _uiType ) );

    } else {

        fprintf(stderr, "UI: None\n");

    }


};

void NativeUIDriver::createUI() {

    _uiSuil = suil_host_new( NativeUIDriver::suilUIWrite, NativeUIDriver::suilPortIndex, NULL, NULL);

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

            _HAS_EXTERNAL_UI = false;

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

    Plugin * _Plugin = _UI->getPlugin();

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

/**
 * UI has resize opt
 */

bool NativeUIDriver::hasResize() {

    LilvWorld * _lilvWorld = _UI->getLilvWorld();

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

LilvNode * NativeUIDriver::getExternalKX() {

    return lilv_new_uri(
        _UI->getPlugin()->getLilvWorld(),
        "http://kxstudio.sf.net/ns/lv2ext/external-ui#Widget"
    );

};


/**
 * External lv studio plugin URI
 *
 */

LilvNode * NativeUIDriver::getExternalLV2() {

    return lilv_new_uri(
        _UI->getPlugin()->getLilvWorld(),
        "http://lv2plug.in/ns/extensions/ui#external"
    );

};


/**
 * Port get by symbol
 */

Port * NativeUIDriver::portBySymbol( Plugin * p, const char * sym ) {

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

void NativeUIDriver::suilUIWrite(
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

uint32_t NativeUIDriver::suilPortIndex( SuilController controller, const char * symbol ) {

    Plugin * p = (Plugin*)controller;

    Port * port = NativeUIDriver::portBySymbol( p, symbol );

    return port ? port->index : LV2UI_INVALID_PORT_INDEX;

};


}; };
