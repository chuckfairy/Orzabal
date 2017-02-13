/**
 * LV2 Plugin
 *
 */
#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

#include <jack/ringbuffer.h>

#include <QScrollArea>

#include <Audio/Plugin.h>

#include "include/types.h"
#include "include/symap.h"
#include "include/semaphone.h"
#include "Host.h"
#include "Port.h"

#define NS_EXT "http://lv2plug.in/ns/ext/"


namespace LV2 {


/**
 * class forward
 */

class UI;
class PluginWorker;


/**
 * Plugin Main fro Audio::Plugin
 */

class Plugin : public Audio::Plugin {

    private:

        /**
         * lilv specific
         */

        const LilvPlugin *  _lilvPlugin;

        LilvWorld * _lilvWorld;

        LilvInstance * _lilvInstance;

        const LV2_Descriptor * _lilvDescriptor;

        char _lilvURI[500];


        /**
         *  LV2 Feature options
         */

        LV2_URI_Map_Feature uri_map = { NULL, &Plugin::uriToId };
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

        const LV2_Extension_Data_Feature ext_data = { NULL };

        /** These features have no data */
        const LV2_Feature buf_size_features[3] = {
            { LV2_BUF_SIZE__powerOf2BlockLength, NULL },
            { LV2_BUF_SIZE__fixedBlockLength, NULL },
            { LV2_BUF_SIZE__boundedBlockLength, NULL }
        };

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


        /**
         *  Instances
         */

        Host * _Host;

        ZixSem _symap_lock;
        size_t longest_sym = 0;


        /**
         * Worker related
         */

        PluginWorker * _worker;
        PluginWorker * _stateWorker;

        ZixSem _worker_lock;

        ZixSem exit_sem;


        /**
         * LV2 Port default values
         */

        float * _defaultValues;


        /**
         * Atom thread lv2
         */

        LV2_Atom_Forge _forge;


        /**
         * Lilv state
         */

        LilvState * _state;


        /**
         * @TODO move mapping URI base
         */

        LV2_URID_Map map;

        LV2_URID_Unmap unmap;

        LilvNode * atom_Chunk;
        LilvNode * atom_Sequence;
        LV2_URID atom_Object;
        LV2_URID atom_eventTransfer;

        LV2_URID _time_position;
        LV2_URID _time_bar;
        LV2_URID _time_barBeat;
        LV2_URID _time_beatUnit;
        LV2_URID _time_beatsPerBar;
        LV2_URID _time_beatsPerMinute;
        LV2_URID _time_frame;
        LV2_URID _time_speed;
        LV2_URID patch_Get;


        /**
         * Timing props
         */

        LV2_Atom* lv2_pos;

        LilvNode * lv2_reportsLatency;

        bool _request_update;

        int sample_rate;

        float ui_update_hz;

        int midi_buf_size = 1024;

        uint32_t midi_event_id;

        uint32_t plugin_latency;

        bool xport_changed;

        int block_length = 4096;

        bool _transportRolling;

        unsigned int buffer_size;

        bool buf_size_set = false;

        int _position;

        int _bpm = 120.0f;


    protected:

        const char * TYPE = "LV2";

        UI * _UI;

        jack_ringbuffer_t * _ringBuffer;

        jack_nframes_t event_delta_t;

        jack_ringbuffer_t * plugin_events;


    public:

        explicit Plugin( const LilvPlugin * p, Host * h );


        /**
         * Virtual construction
         *
         */

        void setPorts();

        void start();

        void run();

        void stop();

        UI * getUI();


        /**
         * UI Widget getter
         */

        QScrollArea * getUIWidget();


        /**
         * Port creation and actions
         */

        Audio::Port * createPort( long portNum );

        void activatePorts();

        void activatePort( long portNum );

        void allocatePortBuffers();

        void allocatePortBuffer( uint32_t i );

        const bool portIsOptional( Port * );

        const bool portIs( Port *, const char * );

        const bool portIsAudio( Port * );

        const bool portIsInput( Port * );

        const bool portIsOutput( Port * );

        const bool portIsControl( Port * );

        const bool portIsEvent( Port * );

        const bool portIsAtom( Port * );

        const bool portIsCV( Port * );


        /**
         * required features checker
         */

        bool hasRequiredFeatures();

        bool lilvFeaturesIsSupported( const char * );


        /**
         * Lilv plugin related
         */

        const LilvPlugin * getLilvPlugin() {

            return _lilvPlugin;

        };

        void setLilvPlugin( const LilvPlugin* p );


        /**
         * Host related
         */

        void setHost( Host * h ) {

            _Host = h;

            setLilvWorld( h->getLilvWorld() );

        };


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

        LilvInstance * getLilvInstance() {

            return _lilvInstance;

        };

        LV2_Handle getLV2Handle();


        /**
         * Plugin worker lock
         */

        ZixSem getWorkerLock() {

            return _worker_lock;

        };


        /**
         * Jack related
         */

        void updateJack( jack_nframes_t );

        void updatePort( uint32_t, jack_nframes_t, LV2_Atom * );

        void updateJackLatency( jack_latency_callback_mode_t );

        void updateJackBufferSize( jack_nframes_t );


        /**
         * LV2 Mapping midi
         */

        Symap * _symap;

        ZixSem symap_lock;


        /**
         * LV2 Mapping feature
         */

        static LV2_URID mapURI( LV2_URID_Map_Handle, const char * );

        static const char * unmapURI( LV2_URID_Map_Handle, LV2_URID );


        /**
          Map function for URI map extension.
          */

        static uint32_t uriToId( LV2_URI_Map_Callback_Data, const char *, const char * );


        /**
         * LV2 Temp path make
         */

        static const char * TEMP_PATH;

        static char * LV2MakePath( LV2_State_Make_Path_Handle, const char * );

};

};
