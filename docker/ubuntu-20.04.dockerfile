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
    >> /etc/apt/apt.conf.d/90fix-hashsum-mismatch

RUN apt-get update 2>&1 | tee -a /buildLog.txt
RUN apt-get upgrade -y 2>&1 | tee -a /buildLog.txt

COPY ./scripts/ubuntu-20.04_installSystemDependencies.sh /tmp/ubuntu-20.04_installSystemDependencies.sh
RUN sh /tmp/ubuntu-20.04_installSystemDependencies.sh 2>&1 | tee -a /buildLog.txt


#
# Disposable container to build external dependencies.
#
FROM units-ubuntu-20_04-base AS units-ubuntu-20_04-external-build
COPY ./scripts/setupExternalDependencies.sh /tmp/setupExternalDependencies.sh
RUN sh /tmp/setupExternalDependencies.sh /usr 2>&1 | tee -a /buildLog.txt


#
# Container equipped with tool and dependencies to build the units source code.
#
FROM units-ubuntu-20_04-base AS units-ubuntu-20_04-build-base
COPY --from=units-ubuntu-20_04-external-build /usr /usr


#
# Disposable container to build the source code from context and install to /usr
#
FROM units-ubuntu-20_04-build-base AS units-ubuntu-20_04-build
COPY . /tmp/units-src

RUN cmake -E make_directory /tmp/units-build
RUN cmake -G Ninja -S /tmp/units-src -B /tmp/units-build    \
    -DCMAKE_BUILD_TYPE:STRING="Release"                     \
    -DCMAKE_INSTALL_PREFIX:PATH=/usr                        \
    -DBUILD_TESTING:BOOL=ON

RUN cmake --build /tmp/units-build --config Release
RUN cmake --install /tmp/units-build --config Release


#
# Container with units package install to /usr.
#
FROM units-ubuntu-20_04-base AS units-ubuntu-20_04-deploy
COPY --from=units-ubuntu-20_04-build /usr /usr


#
# Disposable container to test findability of installed units package.
#
FROM units-ubuntu-20_04-deploy AS units-ubuntu-20_04-deploy-tester

WORKDIR /tmp
RUN curl -L https://github.com/ajakhotia/importTester/archive/main.zip -o /tmp/importTester.zip &&  \
    cmake -E tar -x /tmp/importTester.zip &&                                                        \
    cmake -E rename /tmp/importTester-main /tmp/importTester-src &&                                 \
    cmake -E remove /tmp/importTester.zip

WORKDIR /

RUN cmake -E make_directory /tmp/importTester-build
ENTRYPOINT ["cmake",                                    \
            "-G", "Ninja",                              \
            "-S", "/tmp/importTester-src",              \
            "-B", "/tmp/importTester-build",            \
            "-DIMPORT_TESTER_FIND_units:BOOL=ON"]
