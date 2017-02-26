/**
 * Jack port extension
 */
#pragma once

#include <jack/types.h>

#include <Audio/Port.h>

namespace Jack {

struct Port : public Audio::Port {

    jack_port_t * jack_port;

    size_t buf_size;

};

};
