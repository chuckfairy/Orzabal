/**
 * LV2 Host extended from Jack
 *
 */
#include <stdexcept>
#include <vector>

#include <Jack/Host.h>
#include <Jack/Server.h>
#include <Audio/Plugin.h>

#include "Host.h"
#include "Plugin.h"
#include "Search.h"
#include "JackCallbackEvent.h"
#include "Events/JackLatencyEvent.h"
#include "Events/JackBufferEvent.h"


using std::vector;

namespace LV2 {


/**
 * Construct
 */

Host::Host( Jack::Server * s ) : Jack::Patchbay( s ) {

    _lilvWorld = lilv_world_new();
    lilv_world_load_all( _lilvWorld );

    setServer( s );

    _Search = new Search( this );

};

};
