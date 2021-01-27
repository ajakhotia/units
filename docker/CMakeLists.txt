find_program(DOCKER_EXECUTABLE docker REQUIRED)

add_custom_target(ubuntu-20.04-gnu-docker
        COMMAND
            ${DOCKER_EXECUTABLE}
            build
            --force-rm
            --tag units/ubuntu-gnu-20.04
            --file
            ${CMAKE_CURRENT_LIST_DIR}/ubuntu-gnu-20.04.dockerfile
            ${units_SOURCE_DIR}
        COMMENT
            "Building units on ubuntu 20.04 with GNU")