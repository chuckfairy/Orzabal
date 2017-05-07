/**
 * Native UI driver lv2
 */
#pragma once

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/data-access/data-access.h>
#include <lv2/lv2plug.in/ns/ext/event/event.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/parameters/parameters.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>
#include <lv2/lv2plug.in/ns/ext/port-groups/port-groups.h>
#include <lv2/lv2plug.in/ns/ext/port-props/port-props.h>
#include <lv2/lv2plug.in/ns/ext/presets/presets.h>
#include <lv2/lv2plug.in/ns/ext/resize-port/resize-port.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

#include <lilv/lilv.h>
#include <suil/suil.h>
#include <sratom/sratom.h>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include <Audio/UIDriver.h>

#include <LV2/Plugin.h>
#include <LV2/include/types.h>


namespace LV2 {

/**
 * Forwarding
 *
 */

class UI;


namespace UIs {


/**
 * UI use of lilv
 *
 */

class NativeUIDriver : public Audio::UIDriver {

    public:

        NativeUIDriver();


        /**
         * Virtual loading
         */

        void start();

        void stop();

        void update();

        void resize();


        /**
         * Unique Lilv setups
         */

        static bool isResizeable( UI * );

        bool hasResize();

        void createUI();


        /**
         * Event data
         */

        jack_ringbuffer_t * getPortEvents() {

            return _uiPortEvents;

        };


    protected:

        UI * _UI;

        /**
         * Node types grabs
         */

        LilvNode * getExternalKX();

        LilvNode * getExternalLV2();


        /**
         * Suil statics
         */

        static void suilUIWrite(
            SuilController controller,
            uint32_t port_index,
            uint32_t buffer_size,
            uint32_t protocol,
            const void * buffer
        );


        static uint32_t suilPortIndex( SuilController, const char * );

        static Port * portBySymbol( Plugin *, const char * );

        bool _HAS_EXTERNAL_UI;

        bool _HAS_LILV_UI;


        /**
         * Native ui suil data
         * @TODO allow setting of the external
         */

        const char * _LV2_UI_EXTERNAL = "http://lv2plug.in/ns/extensions/ui#external";

        const char * _NATIVE_UI_TYPE = "http://lv2plug.in/ns/extensions/ui#Qt5UI";

        void * win;


    private:

        /**
         *  Lilv types
         */

        LilvUIs * _lilvUIS;

        const LilvUI * _lilvUI;

        const LilvNode * _uiType;


        /**
         * UI Instances
         */

        SuilHost * _uiSuil;

        SuilInstance * _uiInstance;

        Sratom * _uiSratom;

        jack_ringbuffer_t * _uiPortEvents;

        void * _uiEventBuf;

        void * extuiptr;

        LV2_Extension_Data_Feature ext_data = { NULL };

        LV2_Feature uri_map_feature      = { NS_EXT "uri-map", NULL };
        LV2_Feature map_feature          = { LV2_URID__map, NULL };
        LV2_Feature unmap_feature        = { LV2_URID__unmap, NULL };
        LV2_Feature make_path_feature    = { LV2_STATE__makePath, NULL };
        LV2_Feature sched_feature        = { LV2_WORKER__schedule, NULL };
        LV2_Feature state_sched_feature  = { LV2_WORKER__schedule, NULL };
        LV2_Feature safe_restore_feature = { LV2_STATE__threadSafeRestore, NULL };
        LV2_Feature log_feature          = { LV2_LOG__log, NULL };
        LV2_Feature options_feature      = { LV2_OPTIONS__options, NULL };


        void setNativeUIData();

};

}; };
