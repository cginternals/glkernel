
#
# External dependencies
#

find_package(${META_PROJECT_NAME} REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../")
find_package(GLM 0.9.6 REQUIRED)
find_package(OpenMP)

#
# Executable name and options
#


function(add_own_test scope name idx)

    set(filename "${scope}_fail.cpp")
    set(target "${scope}_${name}_${idx}")
    string(TOUPPER ${target} MACRONAME)

    message(STATUS "Test ${target} in ${filename}")

    if (NOT OPENMP_FOUND)
        message("Loop parallelization in ${target} skipped: OpenMP not found")
    endif()


    #
    # Sources
    #

    set(sources
        ${filename}
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
        EXCLUDE_FROM_ALL TRUE
        EXCLUDE_FROM_DEFAULT_BUILD TRUE
    )


    #
    # Include directories
    #

    target_include_directories(${target}
        PRIVATE
        ${DEFAULT_INCLUDE_DIRECTORIES}
        ${GLM_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${PROJECT_BINARY_DIR}/source/include
    )


    #
    # Libraries
    #

    target_link_libraries(${target}
        PRIVATE
        ${DEFAULT_LIBRARIES}
        ${META_PROJECT_NAME}::glkernel
    )


    #
    # Compile definitions
    #

    target_compile_definitions(${target}
        PRIVATE
        ${MACRONAME}
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

    if(BUILD_TESTING)
        message("CTest ready for registering ${target}")
        # Add the tests.  These invoke "cmake --build ..." which is a
        # cross-platform way of building the given target.
        add_test(NAME ${target}
            COMMAND ${CMAKE_COMMAND} --build . --target ${target} --config $<CONFIGURATION>
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        # Expect these tests to fail (i.e. cmake --build should return
        # a non-zero value)
        set_tests_properties(${target} PROPERTIES WILL_FAIL TRUE)
    endif()

endfunction()



add_own_test(noise normal 1)
add_own_test(noise normal 2)
add_own_test(noise normal 3)
add_own_test(noise normal 4)
add_own_test(noise normal 5)
add_own_test(noise normal 6)
add_own_test(noise uniform 1)
add_own_test(noise uniform 2)
add_own_test(noise uniform 3)
add_own_test(noise uniform 4)
add_own_test(noise uniform 5)
add_own_test(noise uniform 6)
add_own_test(noise uniform 7)

add_own_test(sample poisson_square 1)
add_own_test(sample poisson_square 2)
add_own_test(sample poisson_square 3)
add_own_test(sample poisson_square 4)
