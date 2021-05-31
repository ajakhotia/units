ARG INSTALL_PREFIX=/usr
ARG EXTERNAL_INSTALL_PREFIX=/usr

#
# Base container with tools to build units and its dependencies.
#
FROM ubuntu:20.04 AS units-ubuntu-20_04-base

# Set dpkg to run in non-interactive mode.
ENV DEBIAN_FRONTEND=noninteractive

# Set shell to return failure code if any command in the pipe fails.
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN printf                              \
'Acquire::http::Pipeline-Depth 0;\n     \
Acquire::http::No-Cache true;\n         \
Acquire::BrokenProxy    true;\n'        \
    >> /etc/apt/apt.conf.d/90fix-hashsum-mismatch 2>&1 | tee -a /buildLog.txt

RUN apt-get update 2>&1 | tee -a /buildLog.txt
RUN apt-get upgrade -y 2>&1 | tee -a /buildLog.txt

COPY ./scripts/ubuntu-20.04_installSystemDependencies.sh /tmp/ubuntu-20.04_installSystemDependencies.sh
RUN sh /tmp/ubuntu-20.04_installSystemDependencies.sh 2>&1 | tee -a /buildLog.txt


#
# Disposable container to build external dependencies.
#
FROM units-ubuntu-20_04-base AS units-ubuntu-20_04-external-build
ARG EXTERNAL_INSTALL_PREFIX

COPY ./scripts/setupExternalDependencies.sh /tmp/setupExternalDependencies.sh
RUN sh /tmp/setupExternalDependencies.sh ${EXTERNAL_INSTALL_PREFIX} 2>&1 | tee -a /buildLog.txt


#
# Container equipped with tool and dependencies to build the units source code.
#
FROM units-ubuntu-20_04-base AS units-ubuntu-20_04-build-base
ARG EXTERNAL_INSTALL_PREFIX

COPY --from=units-ubuntu-20_04-external-build ${EXTERNAL_INSTALL_PREFIX} ${EXTERNAL_INSTALL_PREFIX}


#
# Disposable container to build and install the source code from context.
#
FROM units-ubuntu-20_04-build-base AS units-ubuntu-20_04-build
ARG INSTALL_PREFIX
ARG EXTERNAL_INSTALL_PREFIX=/usr


COPY . /tmp/units-src

RUN cmake -E make_directory /tmp/units-build 2>&1 | tee -a /buildLog.txt
RUN cmake -G Ninja -S /tmp/units-src -B /tmp/units-build    \
    -DCMAKE_BUILD_TYPE:STRING="Release"                     \
    -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_PREFIX}           \
    -DCMAKE_PREFIX_PATH:PATH=${EXTERNAL_INSTALL_PREFIX}     \
    -DBUILD_TESTING:BOOL=ON 2>&1 | tee -a /buildLog.txt

RUN cmake --build /tmp/units-build --config Release 2>&1 | tee -a /buildLog.txt
RUN cmake --install /tmp/units-build --config Release 2>&1 | tee -a /buildLog.txt


#
# Container with units package install to user provided install prefix.
#
FROM units-ubuntu-20_04-base AS units-ubuntu-20_04-deploy
ARG INSTALL_PREFIX

COPY --from=units-ubuntu-20_04-build ${INSTALL_PREFIX} ${INSTALL_PREFIX}


#
# Disposable container to test findability of installed units package.
#
FROM units-ubuntu-20_04-deploy AS units-ubuntu-20_04-deploy-tester
ARG INSTALL_PREFIX

RUN curl -L https://github.com/ajakhotia/importTester/archive/main.zip -o /tmp/importTester.zip &&  \
    cmake -E remove_directory /tmp/importTester-src &&                                              \
    cmake -E chdir /tmp cmake -E tar -x /tmp/importTester.zip &&                                    \
    cmake -E rename /tmp/importTester-main /tmp/importTester-src &&                                 \
    cmake -E remove /tmp/importTester.zip 2>&1 | tee -a /buildLog.txt

RUN cmake -E make_directory /tmp/importTester-build 2>&1 | tee -a /buildLog.txt

CMD ["cmake",                                                                       \
    "-G", "Ninja",                                                                  \
    "-S", "/tmp/importTester-src",                                                  \
    "-B", "/tmp/importTester-build",                                                \
    "-DCMAKE_PREFIX_PATH:PATH=\"${INSTALL_PREFIX};${EXTERNAL_INSTALL_PREFIX}\"",    \
    "-DIMPORT_TESTER_FIND_units:BOOL=ON"]
