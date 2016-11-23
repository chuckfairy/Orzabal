/**
 * LV2 Plugin
 *
 */
#pragma once

#include <string.h>

#include <lilv/lilv.h>

#include <Audio/Plugin.h>


class LV2Plugin : public Plugin {

    protected:

        //const char * TYPE = "LV2";

        const LilvPlugin *  _lilvPlugin;


    public:

        LV2Plugin();

        LV2Plugin( const LilvPlugin* p );
        //LV2Plugin( LilvPluginImpl const* p ) {};

        Port createPort( long portNum );

        void setPorts();

};
