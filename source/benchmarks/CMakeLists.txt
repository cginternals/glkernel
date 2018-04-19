
#
# Configure benchmark project and environment
#

# CMake version
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Meta information about the project
set(META_PROJECT_NAME "glkernel")

# Declare project
project("${META_PROJECT_NAME}-benchmarks" C CXX)

# Set policies
set_policy(CMP0028 NEW) # ENABLE  CMP0028: Double colon in target name means ALIAS or IMPORTED target.
set_policy(CMP0054 NEW) # ENABLE  CMP0054: Only interpret if() arguments as variables or keywords when unquoted.
set_policy(CMP0042 NEW) # ENABLE  CMP0042: MACOSX_RPATH is enabled by default.
set_policy(CMP0063 NEW) # ENABLE  CMP0063: Honor visibility properties for all target types.
set_policy(CMP0037 OLD) # DISABLE CMP0037: Target names should not be reserved and should match a validity pattern.

# Compiler settings and options

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CompileOptions.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Custom.cmake)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")
else()
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompileOptions.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Custom.cmake)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()

# Function: Build benchmark and add command to execute it via target "benchmarking"
function(add_benchmark target)
    add_subdirectory(${target})
    
    if(NOT TARGET ${target})
        return()
    endif()
    
    add_dependencies(benchmark ${target})
    add_custom_command(TARGET benchmarking POST_BUILD 
        COMMAND $<TARGET_FILE:${target}> --benchmark_out=bench_results.json --benchmark_out_format=json)
endfunction()

# Build benchmark

add_subdirectory(benchmark)

# Create interface library to link against gmock
add_library(benchmark-dev INTERFACE)

target_include_directories(benchmark-dev
    SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/include/benchmark
)

target_link_libraries(benchmark-dev
    INTERFACE
    benchmark
)


# 
# Target 'benchmarking'
# Does the actual benchmarking
# 

add_custom_target(benchmarking)
set_target_properties(benchmarking PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)


# 
# benchmarks
# 
add_benchmark(glkernel-benchmarks)

