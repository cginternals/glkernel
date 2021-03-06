
# 
# External dependencies
# 

find_package(glm REQUIRED)


# 
# Library name and options
# 

# Target name
set(target glkernel)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(MAKE_C_IDENTIFIER ${target} target_id)
string(TOUPPER ${target_id} target_id)
set(feature_file         "include/${target}/${target}_features.h")
set(export_file          "include/${target}/${target}_export.h")
set(template_export_file "include/${target}/${target}_api.h")
set(export_macro         "${target_id}_API")


# 
# Sources
# 

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/Kernel.h
    ${include_path}/Kernel.hpp
    ${include_path}/constraint.h
    ${include_path}/constraint.hpp
    ${include_path}/glm_compatability.h
    ${include_path}/mask.h
    ${include_path}/mask.hpp
    ${include_path}/noise.h
    ${include_path}/noise.hpp
    ${include_path}/sample.h
    ${include_path}/sample.hpp
    ${include_path}/scale.h
    ${include_path}/scale.hpp
    ${include_path}/sequence.h
    ${include_path}/sequence.hpp
    ${include_path}/shuffle.h
    ${include_path}/shuffle.hpp
    ${include_path}/sort.h
    ${include_path}/sort.hpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# 
# Create library
# 

add_custom_target(${target}-sources SOURCES ${headers})

# Build library
add_library(${target} INTERFACE)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create API export header
generate_template_export_header(${target}
    ${target_id}
    ${template_export_file}
)


# 
# Project options
# 

# none allowed, since interface library (header-only)


# 
# Include directories
# 

target_include_directories(${target}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>

    ${DEFAULT_INCLUDE_DIRECTORIES}
)


# 
# Libraries
# 

target_link_libraries(${target}
    INTERFACE
    glm::glm
)

# 
# Compile definitions
# 

target_compile_definitions(${target}
    INTERFACE
    GLM_FORCE_RADIANS
)

# 
# Compile options
# 

# none required, since interface library (header-only)

# 
# Linker options
# 

# none required, since interface library (header-only)


#
# Target Health
#

#perform_health_checks(
#    ${target}
#    ${headers}
#)


# 
# Deployment
# 

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
