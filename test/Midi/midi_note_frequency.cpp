/**
 * Jack port register should happen upon starting audio server
 */
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "Orzabal/Midi/midi_frequency"

#include <boost/test/unit_test.hpp>

#include <iostream>

#include <Midi/Note.h>
#include <Midi/Frequency.h>

using namespace Orza::Midi;

/**
 * Main port register
 */

BOOST_AUTO_TEST_CASE( midi_frequency ) {

    const float_t base = Frequency::getBaseFrequency( 440 );

    BOOST_CHECK( base == 27.5 );


    const float_t basePyth = Frequency::getBaseFrequency( 432 );

    BOOST_CHECK( basePyth == 27 );


    //Midi consts and checks

    BOOST_CHECK( NOTE_MIN == A0 );

    BOOST_CHECK( getNoteOctave( NOTE_MIN ) == 0 );

    BOOST_CHECK( getNoteOctave( A4 ) == 4 );

    BOOST_CHECK( getNoteOctave( C4 ) == 4 );

};
