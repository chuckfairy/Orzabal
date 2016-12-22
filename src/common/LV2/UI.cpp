/**
 * Plugin UI
 *
 */
#include <jack/jack.h>
#include <jack/midiport.h>

#include <lilv/lilv.h>
#include <suil/suil.h>

#include "UI.h"


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

    /* Get a plugin UI */
    const char* native_ui_type_uri = getNativeUiType();

    _lilvUIS = lilv_plugin_get_uis( _Plugin->getLilvPlugin() );

    const LilvNode* native_ui_type = lilv_new_uri( _Plugin->getLilvWorld(), native_ui_type_uri );

    LILV_FOREACH(uis, u, _lilvUIS) {

        const LilvUI* this_ui = lilv_uis_get( _lilvUIS, u );

        if( lilv_ui_is_supported( this_ui, suil_ui_supported, native_ui_type, &_uiType ) ) {
            /* TODO: Multiple UI support */
            _lilvUI = this_ui;
            break;
        }
    }

    //} else {

        //_lilvUI = lilv_uis_get(jalv.uis, lilv_uis_begin(jalv.uis));

    //}

    if ( ! _lilvUI ) {

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
 * UI type base get
 */

const char * UI::getNativeUiType() {

    return "http://lv2plug.in/ns/extensions/ui#Qt5UI";

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

};
