
find_program(PYTHON "python")

set(generate_target generate)

if(PYTHON)

    message(STATUS "Command ${generate_target}")
    
    add_custom_target(${generate_target})

    add_custom_command(
        TARGET              ${generate_target}
        PRE_BUILD
        WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}/scripts
        COMMAND             ${PYTHON} generate.py -t templates -c ${CMAKE_SOURCE_DIR}/source/tools/glkernel-cli -j ${CMAKE_SOURCE_DIR}/data
        COMMENT             "Generating glkernel JavaScript interface code."
    )

    # Declare target
    
    set_target_properties(${generate_target} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

else()
    message("Command ${generate_target} skipped: python not found")
endif()
