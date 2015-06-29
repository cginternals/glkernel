
# Generate meta-header
configure_file(glkernel-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/glkernel-version.h)

# We do NOT want to deploy this header (at least not for binary packages)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glkernel/glkernel-version.h DESTINATION ${INSTALL_INCLUDE}/glkernel)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)


# Qt5

# good resource: http://www.kdab.com/using-cmake-with-qt-5/

# http://qt-project.org/forums/viewthread/30006/
if(MSVC)
    cmake_policy(SET CMP0020 NEW)
endif()

set(CMAKE_AUTOMOC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)

# Probably works in the next cmake release -> http://www.cmake.org/Bug/view.php?id=13788
# What we do not want is automocs beside the project -> http://www.cmake.org/Bug/view.php?id=13688
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)


# Libraries
set(IDE_FOLDER "")
add_subdirectory(glkernel)

# Applications
set(IDE_FOLDER "Applications")
#add_subdirectory(glkernel-cmd)

if(OPTION_BUILD_DEBUGGER)
	add_subdirectory(debugger)
endif()

# Tests
set(IDE_FOLDER "Tests")
add_subdirectory(tests)
