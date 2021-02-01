FROM ubuntu:20.04 AS units-base

# Set dpkg to run in non-interactive mode.
ENV DEBIAN_FRONTEND=noninteractive

# Set shell to return failure code if any command in the pipe fails.
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN printf                              \
'Acquire::http::Pipeline-Depth 0;\n     \
Acquire::http::No-Cache true;\n         \
Acquire::BrokenProxy    true;\n'        \
    >> /etc/apt/apt.conf.d/90fix-hashsum-mismatch

RUN apt-get update 2>&1 | tee -a /buildLog.txt
RUN apt-get upgrade -y 2>&1 | tee -a /buildLog.txt
RUN apt-get install -y libstdc++6 --no-install-recommends 2>&1 | tee -a /buildLog.txt


FROM units-base AS units-build-base

RUN apt-get install -y --no-install-recommends  \
        ca-certificates                         \
        cmake                                   \
        curl                                    \
        g++                                     \
        ninja-build                             \
        2>&1 | tee -a /buildLog.txt


FROM units-build-base AS units-external-build

WORKDIR /tmp
RUN curl -L https://github.com/ajakhotia/robotFarm/archive/v0.1.0.tar.gz -o /tmp/robotFarm.tar.gz &&    \
    cmake -E tar -x /tmp/robotFarm.tar.gz &&                                                            \
    cmake -E rename /tmp/robotFarm-0.1.0 /tmp/robotFarm-src &&                                          \
    cmake -E remove /tmp/robotFarm.tar.gz

RUN ls /tmp
RUN cmake -E make_directory /tmp/robotFarm-build

RUN cmake -G Ninja -S /tmp/robotFarm-src -B /tmp/robotFarm-build    \
    -DCMAKE_BUILD_TYPE:STRING="Release"                             \
    -DCMAKE_INSTALL_PREFIX:PATH=/usr                                \
    -DROBOT_FARM_BUILD_GOOGLE_TEST:BOOL=ON

RUN cmake --build /tmp/robotFarm-build --config Release -- -j `nproc`
RUN cmake --install /tmp/robotFarm-build --config Release


FROM units-build-base AS units-build

COPY --from=units-external-build /usr /usr
COPY . /tmp/units-src


RUN cmake -E make_directory /tmp/units-build
RUN cmake -G Ninja -S /tmp/units-src -B /tmp/units-build    \
    -DCMAKE_BUILD_TYPE:STRING="Release"                     \
    -DCMAKE_INSTALL_PREFIX:PATH=/usr                        \
    -DBUILD_TESTING:BOOL=ON

RUN cmake --build /tmp/units-build --config Release

WORKDIR /tmp/units-build

RUN ctest -j `nproc`

RUN cmake --install /tmp/units-build --config Release

WORKDIR /


FROM units-build-base AS units-deploy
COPY --from=units-build /usr /usr


FROM units-deploy AS units-deploy-test

RUN mkdir -p /tmp/unitsImportTest-src
RUN printf                                                      \
'cmake_minimum_required(VERSION 3.10)\n                         \
project(unitsImportTest)\n                                      \
find_package(units REQUIRED)\n                                  \
if(NOT TARGET Units::units)\n                                   \
    message(FATAL_ERROR "Units::units target was not found")\n  \
endif()\n'                                                      \
    >> /tmp/unitsImportTest-src/CMakeLists.txt

RUN cmake -E make_directory /tmp/unitsImportTest-build
RUN cmake -G Ninja -S /tmp/unitsImportTest-src -B /tmp/unitsImportTest-build
