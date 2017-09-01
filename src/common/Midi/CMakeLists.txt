
# midi configuration

set( counter 21 )
set( ORZABAL_MIDI_NUMBER_MAX 150 )

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
            continue()
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
