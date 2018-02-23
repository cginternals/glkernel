
# 
# External dependencies
# 

find_package(${META_PROJECT_NAME} REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../")

find_package(glm REQUIRED)
find_package(OpenMP QUIET)

# 
# Executable name and options
# 

# Target name
set(target glkernel-test)
message(STATUS "Test ${target}")

if (NOT OPENMP_FOUND AND NOT OpenMP_FOUND)
    message("Loop parallelization in ${target} skipped: OpenMP not found")
    set(OpenMP_SUPPORTED FALSE)
else()
    if(USE_OPENMP)
        set(OpenMP_SUPPORTED TRUE)
    else()
        set(OpenMP_SUPPORTED FALSE)
    endif()
endif()


# 
# Sources
# 

set(sources
    main.cpp
    noise_test.cpp
    sample_test.cpp
    scale_test.cpp
    sequence_test.cpp
    shuffle_test.cpp
    sort_test.cpp
    tkernel_test.cpp
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    ${sources}
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
    ${GLM_INCLUDE_DIR}
    ${PROJECT_BINARY_DIR}/source/include
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::glkernel
    gmock-dev
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    GLM_FORCE_RADIANS
    $<$<BOOL:${OpenMP_SUPPORTED}>:USE_OPENMP>
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    $<$<BOOL:${OpenMP_SUPPORTED}>:${OpenMP_CXX_FLAGS}>
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:$<$<BOOL:${OpenMP_SUPPORTED}>:${OpenMP_CXX_FLAGS}>>
)
