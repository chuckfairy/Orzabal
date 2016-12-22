/**
 * LV2 Port extension
 */
#pragma once

#include <jack/jack.h>

#include <Audio/Port.h>

namespace LV2 {


/**
 * LV2 Port
 *
 */

struct Port : public Audio::Port {

    const LilvPort * lilv_port;

    jack_port_t * jack_port;

    //LV2_Evbuf*      evbuf;      ///< For MIDI ports, otherwise NULL

    void * widget;

    size_t buf_size;

    uint32_t index;

    void * evbuf;

    int old_api;

};

};
