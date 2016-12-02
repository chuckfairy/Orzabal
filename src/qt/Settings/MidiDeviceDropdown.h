/**
 * Midi device drop down
 *
 */
#pragma once

#include <Midi/Device.h>
#include <Midi/ALSA.h>

#include <QtCore>
#include <QComboBox>

using Midi::Device;


/**
 * Main class
 *
 */

class MidiDeviceDropdown : public QComboBox {

    private:

        Midi::ALSA * midiDriver;


    public:

        MidiDeviceDropdown( QWidget * parent );
        MidiDeviceDropdown();


        /**
         * Add Device append order
         *
         * @param Device Device To be added
         *
         * @return bool
         */
        void addMidiDevice( Device device ) {

            return addMidiDevice( device, -1 );

        };


        /**
         * Add Device
         * will check for dups
         *
         * @param Device Device To be added
         * @param int order Position to be added
         *
         * @return bool
         */
        void addMidiDevice( Device device, const int order );


        /**
         * has Device
         *
         * @return bool
         */
        //bool hasMidiDevice( Device device );

};