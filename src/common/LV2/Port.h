/**
 * LV2 Port extension
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Port.h>

#include "include/lv2_evbuf.h"


namespace LV2 {

/**
 * Class forwarding
 */
class UI;


/**
 * LV2 Port
 *
 */

struct Port : public Audio::Port {

    const LilvPort * lilv_port;

    jack_port_t * jack_port;


    // For MIDI ports, otherwise NULL

    LV2_Evbuf * evbuf;


    void * widget;

    size_t buf_size;

    uint32_t index;

    int old_api;

};


/**
 * Conatiner
 */

struct PortContainer {
	UI * ui;
	Port* port;
};

};
