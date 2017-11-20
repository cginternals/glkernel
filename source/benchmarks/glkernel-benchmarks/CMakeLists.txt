
# 
# External dependencies
# 

find_package(${META_PROJECT_NAME} REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../")
find_package(GLM 0.9.6 REQUIRED)
find_package(OpenMP)

# 
# Executable name and options
# 

# Target name
set(target glkernel-benchmark)
message(STATUS "Benchmark ${target}")

if (NOT OPENMP_FOUND)
    message("Loop parallelization in ${target} skipped: OpenMP not found")
endif()


# 
# Sources
# 

set(sources
    noise_benchmark.cpp
    scale_benchmark.cpp
    shuffle_benchmark.cpp
    sort_benchmark.cpp
    sample_benchmark.cpp
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
    benchmark-dev
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    GLM_FORCE_RADIANS
    $<$<BOOL:"${OPENMP_FOUND}">:USE_OPENMP>
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    $<$<BOOL:"${OPENMP_FOUND}">:${OpenMP_CXX_FLAGS}>
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:$<$<BOOL:"${OPENMP_FOUND}">:${OpenMP_CXX_FLAGS}>>
)
