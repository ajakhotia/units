# syntax=docker/dockerfile:1.7
ARG OS_BASE=ghcr.io/ajakhotia/infracommons/weekly-base/ubuntu-24-04:latest

FROM ${OS_BASE} AS base

ARG OS_BASE
ENV OS_BASE=${OS_BASE}
ENV APT_VAR_CACHE_ID=units-apt-var-cache-${OS_BASE}
ENV APT_LIST_CACHE_ID=units-apt-list-cache-${OS_BASE}
ENV DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# The base image already ships the vendor apt sources and the bootstrap package set. jq is the
# one extra tool needed here because extractDependencies.sh uses it to parse
# systemDependencies.json.
RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    apt-get update &&                                                                              \
    apt-get install -y --no-install-recommends gettext-base jq

RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    --mount=type=bind,src=external/infraCommons/tools/extractDependencies.sh,dst=/tmp/extractDependencies.sh \
    --mount=type=bind,src=systemDependencies.json,dst=/tmp/systemDependencies.json                 \
    apt-get update &&                                                                              \
    apt-get install -y --no-install-recommends                                                     \
      $(sh /tmp/extractDependencies.sh "Basics Compilers" /tmp/systemDependencies.json)


FROM base AS dev-base
ARG TOOLCHAIN=linux-gnu-15
ENV TOOLCHAIN=${TOOLCHAIN}

RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    --mount=type=bind,src=external/infraCommons/tools/extractDependencies.sh,dst=/tmp/extractDependencies.sh \
    --mount=type=bind,src=systemDependencies.json,dst=/tmp/systemDependencies.json                 \
    apt-get update &&                                                                              \
    apt-get install -y --no-install-recommends                                                     \
      $(sh /tmp/extractDependencies.sh "Testing" /tmp/systemDependencies.json)


FROM dev-base AS build
ARG BUILD_TYPE="Release"
ENV BUILD_TYPE=${BUILD_TYPE}

RUN cmake -E make_directory /opt/units

RUN --mount=type=bind,src=.,dst=/tmp/units-src,ro                                                  \
    cmake -G Ninja                                                                                 \
      -S /tmp/units-src                                                                            \
      -B /tmp/units-build                                                                          \
      -DCMAKE_TOOLCHAIN_FILE:FILEPATH=/tmp/units-src/external/infraCommons/cmake/toolchains/${TOOLCHAIN}.cmake \
      -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE}                                                      \
      -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON                                                    \
      -DCMAKE_INSTALL_PREFIX:PATH=/opt/units &&                                                    \
    cmake --build /tmp/units-build &&                                                              \
    cmake --install /tmp/units-build


FROM build AS test
RUN ctest --test-dir /tmp/units-build --output-on-failure


FROM dev-base AS deploy
COPY --from=build /opt/units /opt/units
