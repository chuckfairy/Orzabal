/**
 * Midi note constants
 */
#pragma once

#include <map>
#include <cmath>
#include <ctgmath>

using std::map;


namespace Orza { namespace Midi {

/**
 * Notes enum
 */

enum NoteNumber {
	A0 = 21,
	As0 = 22,
	B0 = 23,
	C0 = 24,
	Cs0 = 25,
	D0 = 26,
	Ds0 = 27,
	E0 = 28,
	F0 = 29,
	Fs0 = 30,
	G0 = 31,
	Gs0 = 32,
	A1 = 33,
	As1 = 34,
	B1 = 35,
	C1 = 36,
	Cs1 = 37,
	D1 = 38,
	Ds1 = 39,
	E1 = 40,
	F1 = 41,
	Fs1 = 42,
	G1 = 43,
	Gs1 = 44,
	A2 = 45,
	As2 = 46,
	B2 = 47,
	C2 = 48,
	Cs2 = 49,
	D2 = 50,
	Ds2 = 51,
	E2 = 52,
	F2 = 53,
	Fs2 = 54,
	G2 = 55,
	Gs2 = 56,
	A3 = 57,
	As3 = 58,
	B3 = 59,
	C3 = 60,
	Cs3 = 61,
	D3 = 62,
	Ds3 = 63,
	E3 = 64,
	F3 = 65,
	Fs3 = 66,
	G3 = 67,
	Gs3 = 68,
	A4 = 69,
	As4 = 70,
	B4 = 71,
	C4 = 72,
	Cs4 = 73,
	D4 = 74,
	Ds4 = 75,
	E4 = 76,
	F4 = 77,
	Fs4 = 78,
	G4 = 79,
	Gs4 = 80,
	A5 = 81,
	As5 = 82,
	B5 = 83,
	C5 = 84,
	Cs5 = 85,
	D5 = 86,
	Ds5 = 87,
	E5 = 88,
	F5 = 89,
	Fs5 = 90,
	G5 = 91,
	Gs5 = 92,
	A6 = 93,
	As6 = 94,
	B6 = 95,
	C6 = 96,
	Cs6 = 97,
	D6 = 98,
	Ds6 = 99,
	E6 = 100,
	F6 = 101,
	Fs6 = 102,
	G6 = 103,
	Gs6 = 104,
	A7 = 105,
	As7 = 106,
	B7 = 107,
	C7 = 108,
	Cs7 = 109,
	D7 = 110,
	Ds7 = 111,
	E7 = 112,
	F7 = 113,
	Fs7 = 114,
	G7 = 115,
	Gs7 = 116,
	A8 = 117,
	As8 = 118,
	B8 = 119,
	C8 = 120,
	Cs8 = 121,
	D8 = 122,
	Ds8 = 123,
	E8 = 124,
	F8 = 125,
	Fs8 = 126,
	G8 = 127,
	Gs8 = 128,
	A9 = 129,
	As9 = 130,
	B9 = 131,
	C9 = 132,
	Cs9 = 133,
	D9 = 134,
	Ds9 = 135,
	E9 = 136,
	F9 = 137,
	Fs9 = 138,
	G9 = 139,
	Gs9 = 140,
	A10 = 141,
	As10 = 142,
	B10 = 143,
	C10 = 144,
	Cs10 = 145,
	D10 = 146,
	Ds10 = 147,
	E10 = 148,
	F10 = 149,

};


/**
 * Note names map
 */

const map<NoteNumber, const char *> NoteNames;


//Note helper
const enum NoteNumber NOTE_MIN = A0;
const enum NoteNumber NOTE_MAX = F10;


/**
 * Note number
 */

NoteNumber getNoteOctave( enum NoteNumber note ) {

    return (NoteNumber) floor( ( note - NOTE_MIN ) / 12 );

};

}; };
