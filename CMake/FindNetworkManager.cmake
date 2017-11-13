# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig)

pkg_check_modules(NM_DEPS REQUIRED libnm )
