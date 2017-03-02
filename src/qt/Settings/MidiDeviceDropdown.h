/**
 * Midi device drop down
 *
 */
#pragma once

#include <Jack/Port.h>

#include <QtCore>
#include <QComboBox>


/**
 * Main class
 *
 */

class MidiDeviceDropdown : public QComboBox {

    private:


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
        void addMidiDevice( Jack::Port * device ) {

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
        void addMidiDevice( Jack::Port *, const int );


        /**
         * has Device
         *
         * @return bool
         */
        //bool hasMidiDevice( Device device );

};
