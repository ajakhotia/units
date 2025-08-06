function(target_add_exported_header)
    set(OPTIONS_ARGUMENTS "")
    set(SINGLE_VALUE_ARGUMENTS TARGET)
    set(MULTI_VALUE_ARGUMENTS HEADERS)

    cmake_parse_arguments("TAEH_PARAM"
            "${OPTIONS_ARGUMENTS}"
            "${SINGLE_VALUE_ARGUMENTS}"
            "${MULTI_VALUE_ARGUMENTS}"
            ${ARGN})

    set(KEYWORD_LIST INTERFACE PUBLIC PRIVATE)

    # Prepend PRIVATE keyword to declare all headers that appear before the
    # first occurrence of an element from the KEYWORD_LIST as private headers.
    list(APPEND PROCESSED_LIST PRIVATE)

    foreach(ITEM ${TAEH_PARAM_HEADERS})
        if(ITEM IN_LIST KEYWORD_LIST)
            list(APPEND PROCESSED_LIST ${ITEM})
            continue()
        endif()

        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ITEM})
            list(APPEND PROCESSED_LIST $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${ITEM}>)
        else()
            list(APPEND PROCESSED_LIST $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${ITEM}>)
        endif()

        list(APPEND PROCESSED_LIST $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${ITEM}>)

    endforeach()

    target_sources(${TAEH_PARAM_TARGET} ${PROCESSED_LIST})

endfunction()


function(add_exported_library)

    set(OPTIONS_ARGUMENTS "")

    set(SINGLE_VALUE_ARGUMENTS
            TARGET
            TYPE
            NAMESPACE
            EXPORT)

    set(MULTI_VALUE_ARGUMENTS
            SOURCES
            HEADERS
            INCLUDE_DIRECTORIES
            LINK_LIBRARIES
            COMPILE_FEATURES
            COMPILE_OPTIONS
            COMPILE_DEFINITIONS)

    cmake_parse_arguments("AEL_PARAM"
            "${OPTIONS_ARGUMENTS}"
            "${SINGLE_VALUE_ARGUMENTS}"
            "${MULTI_VALUE_ARGUMENTS}"
            ${ARGN})

    if((AEL_PARAM_TYPE) AND (NOT AEL_PARAM_TYPE STREQUAL "INTERFACE"))
        message(AUTHOR_WARNING "Prefer to not specify TYPE for libraries other "
                "than for those which are pure INTERFACE / header-only. This "
                "allows the user to request SHARED / STATIC builds using the "
                "-DBUILD_SHARED_LIBS:BOOL=ON/OFF on the commandline as "
                "necessary.")
    endif()

    add_library(${AEL_PARAM_TARGET} ${AEL_PARAM_TYPE})

    if(AEL_PARAM_SOURCES)
        target_sources(${AEL_PARAM_TARGET} PRIVATE ${AEL_PARAM_SOURCES})
    elseif(NOT AEL_PARAM_TYPE STREQUAL "INTERFACE")
        message(FATAL_ERROR "No sources have been provided for library target ${AEL_PARAM_TARGET}")
    endif()


    if(AEL_PARAM_HEADERS)
        target_add_exported_header(TARGET ${AEL_PARAM_TARGET} HEADERS ${AEL_PARAM_HEADERS})
    else()
        message(AUTHOR_WARNING "No headers have been provided for library target ${AEL_PARAM_TARGET}")
    endif()


    if(AEL_PARAM_NAMESPACE)
        add_library(${AEL_PARAM_NAMESPACE}${AEL_PARAM_TARGET} ALIAS ${AEL_PARAM_TARGET})
    else()
        message(AUTHOR_WARNING "No namespace has been provided for library target ${AEL_PARAM_TARGET}")
    endif()


    if(AEL_PARAM_INCLUDE_DIRECTORIES)
        if(AEL_PARAM_TYPE STREQUAL "INTERFACE")
            target_include_directories(${AEL_PARAM_TARGET} INTERFACE
                    $<BUILD_INTERFACE:${AEL_PARAM_INCLUDE_DIRECTORIES}>
                    $<INSTALL_INTERFACE:include>)
        else()
            target_include_directories(${AEL_PARAM_TARGET} PUBLIC
                    $<BUILD_INTERFACE:${AEL_PARAM_INCLUDE_DIRECTORIES}>
                    $<INSTALL_INTERFACE:include>)
        endif()
    else()
        message(AUTHOR_WARNING "No include directories have been provided for library target ${AEL_PARAM_TARGET}")
    endif()


    if(AEL_PARAM_LINK_LIBRARIES)
        target_link_libraries(${AEL_PARAM_TARGET} ${AEL_PARAM_LINK_LIBRARIES})
    endif()


    if(AEL_PARAM_COMPILE_FEATURES)
        target_compile_features(${AEL_PARAM_TARGET} ${AEL_PARAM_COMPILE_FEATURES})
    endif()


    if(AEL_PARAM_COMPILE_OPTIONS)
        target_compile_options(${AEL_PARAM_TARGET} ${AEL_PARAM_COMPILE_OPTIONS})
    endif()


    if(AEL_PARAM_COMPILE_DEFINITIONS)
        target_compile_definitions(${AEL_PARAM_TARGET} ${AEL_PARAM_COMPILE_DEFINITIONS})
    endif()

    # The trailing / is important to avoid having install path that look like <prefix>/include/include.
    install(DIRECTORY ${AEL_PARAM_INCLUDE_DIRECTORIES}/ TYPE INCLUDE
            PATTERN "*.capnp" EXCLUDE
            PATTERN "*.capnp.c++" EXCLUDE)

    install(TARGETS ${AEL_PARAM_TARGET} EXPORT ${AEL_PARAM_EXPORT})

endfunction()


function(add_exported_executable)

    set(OPTIONS_ARGUMENTS "")

    set(SINGLE_VALUE_ARGUMENTS
            TARGET
            NAMESPACE
            EXPORT)

    set(MULTI_VALUE_ARGUMENTS
            SOURCES
            HEADERS
            INCLUDE_DIRECTORIES
            LINK_LIBRARIES
            COMPILE_FEATURES
            COMPILE_OPTIONS
            COMPILE_DEFINITIONS)

    cmake_parse_arguments("AEE_PARAM"
            "${OPTIONS_ARGUMENTS}"
            "${SINGLE_VALUE_ARGUMENTS}"
            "${MULTI_VALUE_ARGUMENTS}"
            ${ARGN})


    add_executable(${AEE_PARAM_TARGET})

    if(AEE_PARAM_SOURCES)
        target_sources(${AEE_PARAM_TARGET} PRIVATE ${AEE_PARAM_SOURCES})
    else()
        message(FATAL_ERROR "No sources have been provided for executable target ${AEE_PARAM_TARGET}")
    endif()


    if(AEE_PARAM_HEADERS)
        target_add_exported_header(TARGET ${AEE_PARAM_TARGET} HEADERS ${AEE_PARAM_HEADERS})
    endif()


    if(AEE_PARAM_NAMESPACE)
        add_executable(${AEE_PARAM_NAMESPACE}${AEE_PARAM_TARGET} ALIAS ${AEE_PARAM_TARGET})
    else()
        message(AUTHOR_WARNING "No namespace has been provided for executable target ${AEE_PARAM_TARGET}")
    endif()


    if(AEE_PARAM_INCLUDE_DIRECTORIES)
        target_include_directories(${AEE_PARAM_TARGET} PRIVATE ${AEE_PARAM_INCLUDE_DIRECTORIES})
    endif()


    if(AEE_PARAM_LINK_LIBRARIES)
        target_link_libraries(${AEE_PARAM_TARGET} PRIVATE ${AEE_PARAM_LINK_LIBRARIES})
    endif()


    if(AEE_PARAM_COMPILE_FEATURES)
        target_compile_features(${AEE_PARAM_TARGET} PRIVATE ${AEE_PARAM_COMPILE_FEATURES})
    endif()


    if(AEE_PARAM_COMPILE_OPTIONS)
        target_compile_options(${AEE_PARAM_TARGET} PRIVATE ${AEE_PARAM_COMPILE_OPTIONS})
    endif()


    if(AEE_PARAM_COMPILE_DEFINITIONS)
        target_compile_definitions(${AEE_PARAM_TARGET} PRIVATE ${AEE_PARAM_COMPILE_DEFINITIONS})
    endif()


    install(TARGETS ${AEE_PARAM_TARGET} EXPORT ${AEE_PARAM_EXPORT})

endfunction()
