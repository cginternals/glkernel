
#
# External dependencies
#

find_package(cppassist REQUIRED)
find_package(cppexpose REQUIRED)
find_package(cppfs     REQUIRED)
find_package(PNG REQUIRED)

#
# Executable name and options
#

# Target name
set(target glkernel-cli)


#
# Sources
#

set(headers
    AbstractKernelExporter.h
    JsonExporter.h
    KernelGenerator.h
    KernelObject.h
    JSInterface.h
    JsonImporter.h
    PngExporter.h
    helper.h
)

set(sources
    main.cpp
    JsonExporter.cpp
    KernelGenerator.cpp
    KernelObject.cpp
    JSInterface.cpp
    JsonImporter.cpp
    PngExporter.cpp
    helper.cpp
)

set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${CMAKE_CURRENT_SOURCE_DIR} "\\\\.h$"
    ${header_group} ${headers})
source_group_by_path(${CMAKE_CURRENT_SOURCE_DIR} "\\\\.cpp$"
    ${source_group} ${sources})


#
# Create executable
#

# Build executable
add_executable(${target}
    ${sources}
    ${headers}
    )


# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
    )


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/source/include
    ${PNG_INCLUDE_DIR}
    )


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    cppassist::cppassist
    cppexpose::cppexpose
    ${PNG_LIBRARY}
    ${META_PROJECT_NAME}::glkernel
    )


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE
    GLM_FORCE_RADIANS
    ${DEFAULT_COMPILE_DEFINITIONS}
    )


#
# Compile options
#

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
    )


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    )

#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
)


#
# Deployment
#

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT tools
    BUNDLE  DESTINATION ${INSTALL_BIN} COMPONENT tools
    )
