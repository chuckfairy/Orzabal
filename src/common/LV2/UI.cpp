/**
 * Plugin UI
 *
 */
#include "UI.h"


namespace LV2 {

/**
 * construct
 */
UI::UI();

void UI::start() {

    /* Get a plugin UI */
    const char* native_ui_type_uri = jalv_native_ui_type(&jalv);
    jalv.uis = lilv_plugin_get_uis(jalv.plugin);
    if (!jalv.opts.generic_ui && native_ui_type_uri) {
        const LilvNode* native_ui_type = lilv_new_uri(jalv.world, native_ui_type_uri);
        LILV_FOREACH(uis, u, jalv.uis) {
            const LilvUI* this_ui = lilv_uis_get(jalv.uis, u);
            if (lilv_ui_is_supported(this_ui,
                        suil_ui_supported,
                        native_ui_type,
                        &jalv.ui_type)) {
                /* TODO: Multiple UI support */
                jalv.ui = this_ui;
                break;
            }
        }
    } else if (!jalv.opts.generic_ui && jalv.opts.show_ui) {
        jalv.ui = lilv_uis_get(jalv.uis, lilv_uis_begin(jalv.uis));
    }
    if (!jalv.ui) {
        LILV_FOREACH(uis, u, jalv.uis) {
            const LilvUI* ui = lilv_uis_get(jalv.uis, u);
            const LilvNodes* types = lilv_ui_get_classes(ui);
            LILV_FOREACH(nodes, t, types) {
                const char * pt = lilv_node_as_uri(lilv_nodes_get(types, t));
                if (!strcmp(pt, "http://kxstudio.sf.net/ns/lv2ext/external-ui#Widget")) {
                    jalv.externalui = true;
                    jalv.ui = ui;
                    jalv.ui_type = jalv.nodes.ui_externalkx;
                } else if (!strcmp(pt, "http://lv2plug.in/ns/extensions/ui#external")) {
                    jalv.externalui = true;
                    jalv.ui_type = jalv.nodes.ui_externallv;
                    jalv.ui = ui;
                }
            }
        }
    }

};

void UI::stop();

};
