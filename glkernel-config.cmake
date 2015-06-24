
set(GLKERNEL_INCLUDE_DIRS "")
set(GLKERNEL_LIBRARIES "")

# Definition of function "find" with two mandatory arguments, "LIB_NAME" and "HEADER".
macro (find LIB_NAME HEADER)

    set(HINT_PATHS ${ARGN})

    if (${LIB_NAME} STREQUAL "glkernel")
        set(LIB_NAME_UPPER GLKERNEL)
        set(LIBNAME glkernel)
    else()
        string(TOUPPER GLKERNEL_${LIB_NAME} LIB_NAME_UPPER)
        set(LIBNAME ${LIB_NAME})
    endif()

    find_path(
	${LIB_NAME_UPPER}_INCLUDE_DIR
	${HEADER}
        ${ENV_GLKERNEL_DIR}/include
        ${ENV_GLKERNEL_DIR}/source/${LIB_NAME}/include
        ${GLKERNEL_DIR}/include
        ${GLKERNEL_DIR}/source/${LIB_NAME}/include
        ${ENV_PROGRAMFILES}/glkernel/include
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where ${HEADER} resides"
    )


    find_library(
	${LIB_NAME_UPPER}_LIBRARY_RELEASE
        NAMES ${LIBNAME}
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} library"
    )
    find_library(
	${LIB_NAME_UPPER}_LIBRARY_DEBUG
        NAMES ${LIBNAME}d
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} debug library"
    )
    

    if(${LIB_NAME_UPPER}_LIBRARY_RELEASE AND ${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY "optimized" ${${LIB_NAME_UPPER}_LIBRARY_RELEASE} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    elseif(${LIB_NAME_UPPER}_LIBRARY_RELEASE)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_RELEASE})
    elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    endif()

    list(APPEND GLKERNEL_INCLUDE_DIRS ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    list(APPEND GLKERNEL_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARY})

    # DEBUG MESSAGES
    # message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
    # message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
    # message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
    # message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endmacro(find)


# load standard CMake arguments (c.f. http://stackoverflow.com/questions/7005782/cmake-include-findpackagehandlestandardargs-cmake)
include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(GLKERNEL_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENV_PROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{GLKERNEL_DIR}" ENV_GLKERNEL_DIR)

set(LIB_PATHS
    ${GLKERNEL_DIR}/build
    ${GLKERNEL_DIR}/build/Release
    ${GLKERNEL_DIR}/build/Debug
    ${GLKERNEL_DIR}/build-release
    ${GLKERNEL_DIR}/build-debug
    ${GLKERNEL_DIR}/lib
    ${ENV_GLKERNEL_DIR}/lib
    ${ENV_PROGRAMFILES}/glkernel/lib
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    /usr/lib64
    /usr/local/lib64
    /sw/lib64
    /opt/local/lib64
)

# Find libraries
find(fiblib fiblib/fiblib_api.h ${LIB_PATHS})

if(GLKERNEL_FIBLIB_LIBRARY)
  # add dependencies
endif()


# DEBUG
# message("GLKERNEL_INCLUDE_DIRS  = ${GLKERNEL_INCLUDE_DIRS}")
# message("GLKERNEL_LIBRARIES = ${GLKERNEL_LIBRARIES}")

find_package_handle_standard_args(GLKERNEL DEFAULT_MSG GLKERNEL_LIBRARIES GLKERNEL_INCLUDE_DIRS)
mark_as_advanced(GLKERNEL_FOUND)
