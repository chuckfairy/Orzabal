
# midi configuration

set( counter 21 )
set( ORZABAL_MIDI_NUMBER_MAX 150 )

set( ORZABAL_MIDI_CONTROL_MIN 14 )
set( ORZABAL_MIDI_CONTROL_MAX 31 )

set( ORZABAL_MIDI_LETER_NAMES
    "A"
    "As"
    "B"
    "C"
    "Cs"
    "D"
    "Ds"
    "E"
    "F"
    "Fs"
    "G"
    "Gs"
)

set( ORZABAL_MIDI_NAMES_DEFINITION "" )
set( ORZABAL_MIDI_NAMES_ARRAY "" )
set( ORZABAL_MIDI_NAME_LAST "" )

foreach( octave RANGE 10 )

    # midi name

    foreach( midi_name ${ORZABAL_MIDI_LETER_NAMES} )

        # Name def

        set( note_name "${midi_name}${octave}" )

        if( ${counter} MATCHES "${ORZABAL_MIDI_NUMBER_MAX}" )
            break()
        endif()

        set( note_definition_name "\t${note_name} = ${counter},\n" )

        set( ORZABAL_MIDI_NAMES_ARRAY "${ORZABAL_MIDI_NAMES_ARRAY}${note_definition_name}" )

        MATH( EXPR counter "${counter} + 1" )

        set( ORZABAL_MIDI_NAME_LAST "${note_name}" )

    endforeach()

endforeach()

configure_file( Note.h.in Note.h)


# Frequency config

set( ORZABAL_FREQUENCY_DEFAULT_A4 "440" )

configure_file( Config/Frequency.h.in Config/Frequency.h)


# Midi Control config

set( ORZABAL_MIDI_CONTROLS_DEFINITION "" )

foreach( control_num RANGE ${ORZABAL_MIDI_CONTROL_MIN} ${ORZABAL_MIDI_CONTROL_MAX} )

    set( control_definition_name "\tCONTROL_${control_num} = ${control_num},\n" )

    set( ORZABAL_MIDI_CONTROLS_DEFINITION "${ORZABAL_MIDI_CONTROLS_DEFINITION}${control_definition_name}" )

endforeach()

configure_file( Control.h.in Control.h)
