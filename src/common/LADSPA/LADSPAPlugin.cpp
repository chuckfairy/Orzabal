/**
 * Plugin class
 *
 */
#include <stdio.h>
#include <string.h>

#include "ladspa.h"

#include "LADSPAPlugin.h"


/**
 * Construct
 *
 */

LADSPAPlugin::LADSPAPlugin( const LADSPA_Descriptor * des ) {

	setDescriptor( des );

};

void LADSPAPlugin::setDescriptor( const LADSPA_Descriptor * des ) {

    _descriptor = des;

    strcpy( name, des->Name );

    setPorts();

};


/**
 * Set ports from descriptor
 * loops thru ports
 *
 */

void LADSPAPlugin::setPorts() {

    long i;

    for( i = 0; i < _descriptor->PortCount; i++ ) {

        LADSPAPort port = createPort( i );

        setPort( i, port );

    }

};


/**
 * Create port struct from _descriptor
 *
 */

LADSPAPort LADSPAPlugin::createPort( long portNum ) {

    //init struct

    LADSPAPort portReturn {
        _descriptor->PortNames[portNum],
        LADSPA_IS_PORT_AUDIO( _descriptor->PortDescriptors[portNum] ),
        LADSPA_IS_PORT_CONTROL( _descriptor->PortDescriptors[portNum] ),
        LADSPA_IS_PORT_INPUT( _descriptor->PortDescriptors[portNum] ),
        LADSPA_IS_PORT_OUTPUT( _descriptor->PortDescriptors[portNum] )
    };


    //Control bounds

    LADSPA_PortRangeHintDescriptor hint = _descriptor->PortRangeHints[portNum].HintDescriptor;

    if( LADSPA_IS_HINT_BOUNDED_BELOW( hint ) || LADSPA_IS_HINT_BOUNDED_ABOVE( hint ) ) {

        if( LADSPA_IS_HINT_BOUNDED_BELOW( hint ) ) {

            portReturn.lowerBound = _descriptor->PortRangeHints[ portNum ].LowerBound;

        }

        if( LADSPA_IS_HINT_BOUNDED_ABOVE( hint ) ) {

            portReturn.upperBound = _descriptor->PortRangeHints[ portNum ].UpperBound;

        }

    }

    return portReturn;

};


/**
 * Set port
 *
 * @param long index To be mapped to
 * @param LADSPAPort port To be set
 *
 */

void LADSPAPlugin::setPort( long index, LADSPAPort port ) {

    //Main map

    _ports[ index ] = port;


    //Set io

    if( port.isAudio ) {

        if( port.isInput ) {

            _inputs.push_back( index );

        } else if( port.isOutput ) {

            _outputs.push_back( index );

        }

        _audioPorts.push_back( index );

    }


    //Port controls

    if( port.isControl ) {

        _controlPorts.push_back( index );

    }

};
