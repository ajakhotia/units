function(add_clang_format)
    set(OPTIONS_ARGUMENTS "REQUIRED")
    set(SINGLE_VALUE_ARGUMENTS TARGET VERSION)
    set(MULTI_VALUE_ARGUMENTS "")

    cmake_parse_arguments("ACF_PARAM"
            "${OPTIONS_ARGUMENTS}"
            "${SINGLE_VALUE_ARGUMENTS}"
            "${MULTI_VALUE_ARGUMENTS}"
            ${ARGN})

    find_program(CLANG_FORMAT clang-format-${ACF_PARAM_VERSION} NO_CACHE)
    find_program(XARGS xargs NO_CACHE)

    if(CLANG_FORMAT)
        message(STATUS "Found clang-format program with version "
                "${ACF_PARAM_VERSION} at ${CLANG_FORMAT}")
    else()
        message($<IF:${ACF_PARAM_REQUIRED},SEND_ERROR,STATUS>
                "Unable to find clang-format for version ${ACF_PARAM_VERSION}.")
    endif()

    if(XARGS)
        message(STATUS "Found xargs program at ${XARGS}")
    else()
        if(ACF_PARAM_REQUIRED)
            message(SEND_ERROR "Unable to find xargs")
        else()
            message(STATUS "Unable to find xargs. Skipping setting up the "
                    "formatting target ${ACF_PARAM_TARGET}.")
        endif()
    endif()

    add_custom_target(${ACF_PARAM_TARGET}
            COMMAND
                ${CLANG_FORMAT} --version
            COMMAND
                find
                    -not -path \"*build*\" -and
                    -not -path \"${CMAKE_BINARY_DIR}\" -and
                    \\\(
                        -iname *.cpp -o -iname *.hpp -o
                        -iname *.c -o -iname *.h -o
                        -iname *.cc -o -iname *.hh
                    \\\) | ${XARGS} ${CLANG_FORMAT} -style=file -i
            WORKING_DIRECTORY
                ${PROJECT_SOURCE_DIR}
            COMMENT
                "Formatting files in ${PROJECT_SOURCE_DIR} using clang format at
                : ${CLANG_FORMAT}")
endfunction()
