/**
 * Control range
 */
#pragma once

#include <iostream>

#include "Plugin.h"
#include "UI.h"
#include "Port.h"
#include "PluginPortContainer.h"

#include <Midi/Control.h>


using Orza::Midi::ControlPort;
using Orza::Midi::ControlRange;

namespace Audio {

template<typename ControlPort>
class MidiControlRange {

    public:

        explicit MidiControlRange( ControlPort * controlPort,
            Plugin * plugin,
            Port * port
        ) :
            _ControlPort( controlPort ),
            _Plugin( plugin ),
            _port( port )
        {
        };

        explicit MidiControlRange( ControlPort * port, PluginPortContainer * container ) :
            _ControlPort( port ),
            _Plugin( container->plugin ),
            _port( container->port )

        {

        };

        /**
         * Min and max
         */

        void setMin( float newMin ) {

            _min = newMin;

            truncate();

        };

        void setMax( float newMax ) {

            _max = newMax;

            truncate();

        };


        /**
         * Getters
         */

        float getMin() {

            return _min;

        };

        float getMax() {

            return _max;

        };

        /**
         * Range
         */

        void setRangeType( ControlRange range) {

            _rangeType = range;

        };


        /**
         * Main update from value 0-127
         */

        void setFromMidiValue( float value ) {

            _port->control = getValueFromMidi( value );

            update();

        };


        /**
         * Getters
         */

        float getValueFromMidi( float value ) {

            float percent = ( ( 127.0 + value ) / 127.0 ) - 1.0;

            float output = ( ( _max - _min ) * percent ) + _min;

            std::cout << "MIDI VALUE OUT " << output << "\n";

            return output;

        };


        /**
         * Main update for all
         */

        void update() {

            _Plugin->getUI()->updateDrivers();

        };

        /**
         * truncate from min or max
         */

        void truncate() {

            if( _min > _port->control ) {

                _port->control = _min;

            } else if( _max < _port->control ) {

                _port->control = _max;

            } else {

                return;

            }

            update();

        };


    private:

        /**
         * Internals
         */

        float _min = 0.0;
        float _max = 0.0;

        ControlPort * _ControlPort;
        Plugin * _Plugin;
        Port * _port;

        ControlRange _rangeType = Orza::Midi::RANGE_LINEAR;


};

};
