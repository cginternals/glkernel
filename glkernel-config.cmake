
set(GLKERNEL_INCLUDE_DIRS "")

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
    
    list(APPEND GLKERNEL_INCLUDE_DIRS ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    
    # DEBUG MESSAGES
    # message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")

endmacro(find)


# load standard CMake arguments (c.f. http://stackoverflow.com/questions/7005782/cmake-include-findpackagehandlestandardargs-cmake)
include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(GLKERNEL_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENV_PROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{GLKERNEL_DIR}" ENV_GLKERNEL_DIR)

# Find libraries
find(glkernel glkernel/Kernel.h)


# DEBUG
# message("GLKERNEL_INCLUDE_DIRS  = ${GLKERNEL_INCLUDE_DIRS}")

find_package_handle_standard_args(GLKERNEL DEFAULT_MSG GLKERNEL_INCLUDE_DIRS)
mark_as_advanced(GLKERNEL_FOUND)
