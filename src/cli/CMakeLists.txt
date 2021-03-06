# CLI common lib
project(orzabal-cli CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

find_package( CXXOpts REQUIRED )

file( GLOB
	ORZABAL_CLI_INCLUDE_FILES
	${CXXOPTS_INCLUDE_FILES}
	"*.h"
	"*.cpp"
)


## Building
# create orzabal-gui library
add_library(orzabal-cli STATIC ${ORZABAL_CLI_INCLUDE_FILES} )
add_executable(orzabal-cli-app "Main/main.cpp" ${ORZABAL_CLI_INCLUDE_FILES} )

set_target_properties(orzabal-cli PROPERTIES LINKER_LANGUAGE CXX)

set( ORZABAL_CLI_INCLUDE_DIRS
	"${LIBORZA_ROOT_PATH}/lib-src"
	"${LIBORZA_ROOT_PATH}/src"
	"${LIBORZA_ROOT_PATH}/src/common"
	"${ORZABAL_ROOT_PATH}/src"
	"${ORZABAL_ROOT_PATH}/lib-src"
	"${ORZABAL_ROOT_PATH}/lib-src/liborza/src"
	"${ORZABAL_ROOT_PATH}/lib-src/liborza/lib-src"
	"${ORZABAL_ROOT_PATH}/lib-src/liborza/src/common"
	"${CMAKE_BINARY_DIR}/lib-src/liborza/src"

	"${CMAKE_CURRENT_BINARY_DIR}/../"
	${CXXOPTS_INCLUDE_DIRS}
)

include_directories( ${ORZABAL_CLI_INCLUDE_DIRS} )

target_link_libraries( orzabal-cli
	liborza-common-jack
	liborza-common-plugin
	dl
	jack
)

target_link_libraries( orzabal-cli-app
	liborza-common-jack
	liborza-common-plugin
	dl
	jack
)


## Installing

#install(TARGETS orzabal-cli
	#DESTINATION "${ORZABAL_LIB_PATH}"
#)

install( TARGETS
   orzabal-cli
   EXPORT orzabal-cli
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)


# copy public include files
#install(FILES
	#${ORZABAL_GUI_INCLUDE_FILES}
	#DESTINATION ${ORZABAL_LIB_PATH}/orzabal-cli)


## create export file which can be imported by other cmake projects
#install(EXPORT orzabal-cli_export
	#NAMESPACE sample::
	#DESTINATION lib/cmake/orzabal-cli_lib
	#)
