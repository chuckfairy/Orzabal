# ODROID finder

EXEC_PROGRAM( "cat /proc/cpuinfo | grep -o ODROID.*"
    OUTPUT_VARIABLE ODROID_TYPE )

if( "${ODROID_TYPE}" STREQUAL "" )
    set( IS_ODROID false )
else()
    set( IS_ODROID true )
endif()
