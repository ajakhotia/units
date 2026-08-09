add_custom_target(unitsDockerBuildUbuntu2204LinuxGnu15
    COMMAND
      bash -c "docker buildx build --progress=plain                                                 \
          --force-rm                                                                                \
          --tag ghcr.io/ajakhotia/units/ubuntu-22-04/linux-gnu-15:latest                            \
          --build-arg OS_BASE=ghcr.io/ajakhotia/infracommons/weekly-base/ubuntu-22-04:latest        \
          --build-arg TOOLCHAIN=linux-gnu-15                                                        \
          --file ${CMAKE_CURRENT_LIST_DIR}/ubuntu.dockerfile                                        \
          ${units_SOURCE_DIR}"
    WORKING_DIRECTORY
      ${units_SOURCE_DIR}
    COMMENT
      "Building units docker image for ubuntu 22.04 with linux-gnu-15"
    VERBATIM
    USES_TERMINAL)

add_custom_target(unitsDockerBuildUbuntu2404LinuxGnu15
    COMMAND
      bash -c "docker buildx build --progress=plain                                                 \
          --force-rm                                                                                \
          --tag ghcr.io/ajakhotia/units/ubuntu-24-04/linux-gnu-15:latest                            \
          --build-arg OS_BASE=ghcr.io/ajakhotia/infracommons/weekly-base/ubuntu-24-04:latest        \
          --build-arg TOOLCHAIN=linux-gnu-15                                                        \
          --file ${CMAKE_CURRENT_LIST_DIR}/ubuntu.dockerfile                                        \
          ${units_SOURCE_DIR}"

    WORKING_DIRECTORY
      ${units_SOURCE_DIR}
    COMMENT
      "Building units docker image for ubuntu 24.04 with linux-gnu-15"
    VERBATIM
    USES_TERMINAL)

add_custom_target(unitsDockerBuildUbuntu2604LinuxGnu15
    COMMAND
      bash -c "docker buildx build --progress=plain                                                 \
          --force-rm                                                                                \
          --tag ghcr.io/ajakhotia/units/ubuntu-26-04/linux-gnu-15:latest                            \
          --build-arg OS_BASE=ghcr.io/ajakhotia/infracommons/weekly-base/ubuntu-26-04:latest        \
          --build-arg TOOLCHAIN=linux-gnu-15                                                        \
          --file ${CMAKE_CURRENT_LIST_DIR}/ubuntu.dockerfile                                        \
          ${units_SOURCE_DIR}"
    WORKING_DIRECTORY
      ${units_SOURCE_DIR}
    COMMENT
      "Building units docker image for ubuntu 26.04 with linux-gnu-15"
    VERBATIM
    USES_TERMINAL)
