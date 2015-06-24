
# Generate meta-header
configure_file(glkernel-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/glkernel-version.h)

# We do NOT want to deploy this header (at least not for binary packages)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glkernel/glkernel-version.h DESTINATION ${INSTALL_INCLUDE}/glkernel)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Libraries
set(IDE_FOLDER "")
add_subdirectory(glkernel)

# Applications

if(OPTION_BUILD_DEBUGGER)

	set(IDE_FOLDER "Applications")
	add_subdirectory(debugger)

endif()

# Tests
set(IDE_FOLDER "Tests")
add_subdirectory(tests)
