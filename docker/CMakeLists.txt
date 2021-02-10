find_program(DOCKER_EXECUTABLE docker REQUIRED)


add_custom_target(docker-units-ubuntu-20_04-build-base
        COMMAND
            ${DOCKER_EXECUTABLE}
            build
            --force-rm
            --target units-ubuntu-20_04-build-base
            --tag units/ubuntu_20.04/build/base
            --file ${CMAKE_CURRENT_LIST_DIR}/ubuntu-20.04.dockerfile
            ${units_SOURCE_DIR}
        COMMENT
            "Building units-ubuntu-20_04-build-base")


add_custom_target(docker-units-ubuntu-20_04-deploy-tester
        COMMAND
            ${DOCKER_EXECUTABLE}
            build
            --force-rm
            --target units-ubuntu-20_04-deploy-tester
            --tag units/ubuntu_20.04/deploy/tester
            --file ${CMAKE_CURRENT_LIST_DIR}/ubuntu-20.04.dockerfile
            ${units_SOURCE_DIR}
        COMMAND
            ${DOCKER_EXECUTABLE}
            run
            units/ubuntu_20.04/deploy/tester
        COMMENT
            "Building and running units-ubuntu-20_04-deploy-tester")


add_custom_target(docker-units-ubuntu-20_04-deploy
        COMMAND
            ${DOCKER_EXECUTABLE}
            build
            --force-rm
            --target units-ubuntu-20_04-deploy
            --tag units/ubuntu_20.04/deploy
            --file ${CMAKE_CURRENT_LIST_DIR}/ubuntu-20.04.dockerfile
            ${units_SOURCE_DIR}
        COMMENT
            "Building units-ubuntu-20_04-deploy")