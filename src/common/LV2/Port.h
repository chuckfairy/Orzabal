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

    const LilvPort* lilv_port;

    jack_port_t*    jack_port;

    //LV2_Evbuf*      evbuf;      ///< For MIDI ports, otherwise NULL

    void*           widget;     ///< Control widget, if applicable

    size_t          buf_size;   ///< Custom buffer size, or 0

    uint32_t        index;      ///< Port index

    bool            old_api;    ///< True for event, false for atom

};

};
