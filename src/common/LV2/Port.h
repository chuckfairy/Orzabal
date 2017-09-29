/**
 * LV2 Port extension
 */
#pragma once

#include <jack/jack.h>

#include <Jack/Port.h>

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

struct Port : public Jack::Port {

    const LilvPort * lilv_port;


    // For MIDI ports, otherwise NULL

    LV2_Evbuf * evbuf = nullptr;


    void * widget;

    int old_api;

};

};
