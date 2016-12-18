/**
 * LV2 Plugin
 *
 */
#pragma once

#include <iostream>
#include <string.h>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>


class LV2Plugin : public Audio::Plugin {

    private:

        const LilvPlugin *  _lilvPlugin;

        void setLilvPlugin();

        char _lilvURI[500];

	/* Build options array to pass to plugin */
	//const LV2_Options_Option options[] = {
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.param_sampleRate,
		  //sizeof(float), jalv.urids.atom_Float, &jalv.sample_rate },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_minBlockLength,
		  //sizeof(int32_t), jalv.urids.atom_Int, &jalv.block_length },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_maxBlockLength,
		  //sizeof(int32_t), jalv.urids.atom_Int, &jalv.block_length },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.bufsz_sequenceSize,
		  //sizeof(int32_t), jalv.urids.atom_Int, &jalv.midi_buf_size },
		//{ LV2_OPTIONS_INSTANCE, 0, jalv.urids.ui_updateRate,
		  //sizeof(float), jalv.urids.atom_Float, &jalv.ui_update_hz },
		//{ LV2_OPTIONS_INSTANCE, 0, 0, 0, 0, NULL }
	//};

    protected:

        const char * TYPE = "LV2";


    public:

        LV2Plugin();

        LV2Plugin( const LilvPlugin* p );

        Audio::Port createPort( long portNum );

        void setPorts();

        void setLilvPlugin( const LilvPlugin* p );

        void start();

};
