/**
 * LV2 Plugin
 *
 */
#pragma once

#include <iostream>
#include <string.h>

#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/data-access/data-access.h>
#include <lv2/lv2plug.in/ns/ext/event/event.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/parameters/parameters.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>
#include <lv2/lv2plug.in/ns/ext/port-groups/port-groups.h>
#include <lv2/lv2plug.in/ns/ext/port-props/port-props.h>
#include <lv2/lv2plug.in/ns/ext/presets/presets.h>
#include <lv2/lv2plug.in/ns/ext/state/state.h>
#include <lv2/lv2plug.in/ns/ext/time/time.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>


#include <lilv/lilv.h>

#include <Audio/Plugin.h>

#include "include/types.h"
#include "Host.h"

#define NS_EXT "http://lv2plug.in/ns/ext/"


namespace LV2 {

class Plugin : public Audio::Plugin {

    private:

        const LilvPlugin *  _lilvPlugin;

        LilvWorld * _lilvWorld;

        LilvInstance * _lilvInstance;

        const LV2_Descriptor * _lilvDescriptor;

        char _lilvURI[500];

        LV2_Feature uri_map_feature      = { NS_EXT "uri-map", NULL };
        LV2_Feature map_feature          = { LV2_URID__map, NULL };
        LV2_Feature unmap_feature        = { LV2_URID__unmap, NULL };
        LV2_Feature make_path_feature    = { LV2_STATE__makePath, NULL };
        LV2_Feature sched_feature        = { LV2_WORKER__schedule, NULL };
        LV2_Feature state_sched_feature  = { LV2_WORKER__schedule, NULL };
        LV2_Feature safe_restore_feature = { LV2_STATE__threadSafeRestore, NULL };
        LV2_Feature log_feature          = { LV2_LOG__log, NULL };
        LV2_Feature options_feature      = { LV2_OPTIONS__options, NULL };
        LV2_Feature def_state_feature    = { LV2_STATE__loadDefaultState, NULL };

        const LV2_URI_Map_Feature uri_map = { NULL, &uri_to_id };

        const LV2_Extension_Data_Feature ext_data = { NULL };

        /** These features have no data */
        const LV2_Feature buf_size_features[3] = {
            { LV2_BUF_SIZE__powerOf2BlockLength, NULL },
            { LV2_BUF_SIZE__fixedBlockLength, NULL },
            { LV2_BUF_SIZE__boundedBlockLength, NULL } };

        const LV2_Feature* features[12] = {
            &uri_map_feature, &map_feature, &unmap_feature,
            &sched_feature,
            &log_feature,
            &options_feature,
            &def_state_feature,
            &safe_restore_feature,
            &buf_size_features[0],
            &buf_size_features[1],
            &buf_size_features[2],
            NULL
        };


    protected:

        const char * TYPE = "LV2";


    public:

        Plugin( const LilvPlugin *, Host * );

        Audio::Port createPort( long portNum );


        /**
         * Virtual construction
         *
         */

        void setPorts();

        void start();


        /**
         * Lilv plugin related
         */

        const LilvPlugin * getLilvPlugin() {

            return _lilvPlugin;

        };

        void setLilvPlugin( const LilvPlugin* p );


        /**
         * lilv world related
         *
         */

        LilvWorld * getLilvWorld() {

            return _lilvWorld;

        };

        void setLilvWorld( LilvWorld * w ) {

            _lilvWorld = w;

        };

};

};
