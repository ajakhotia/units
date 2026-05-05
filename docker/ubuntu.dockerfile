# syntax=docker/dockerfile:1.7
ARG OS_BASE=ubuntu:22.04

FROM ${OS_BASE} AS base

ARG OS_BASE
ENV OS_BASE=${OS_BASE}
ENV APT_VAR_CACHE_ID=units-apt-var-cache-${OS_BASE}
ENV APT_LIST_CACHE_ID=units-apt-list-cache-${OS_BASE}
ENV DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN printf '%s\n'                                                                                  \
    'path-exclude /usr/share/doc/*'                                                                \
    'path-exclude /usr/share/man/*'                                                                \
    'path-include /usr/share/locale/locale.alias'                                                  \
    'path-include /usr/share/locale/en*/*'                                                         \
    'path-exclude /usr/share/locale/*'                                                             \
    'path-exclude /usr/share/info/*'                                                               \
    > /etc/dpkg/dpkg.cfg.d/01_nodoc

RUN printf '%s\n'                                                                                  \
    'Acquire::http::Pipeline-Depth 0;'                                                             \
    'Acquire::https::Pipeline-Depth 0;'                                                            \
    'Acquire::http::No-Cache true;'                                                                \
    'Acquire::https::No-Cache true;'                                                               \
    'Acquire::BrokenProxy    true;'                                                                \
    >> /etc/apt/apt.conf.d/90fix-hashsum-mismatch

# Make apt resilient to flaky upstreams (e.g., Launchpad PPA hosting under stress):
# 5 retries with short per-request timeouts so each failed attempt fails fast and
# we get more shots at reaching a healthy backend behind the load balancer.
RUN printf '%s\n'                                                                                  \
    'Acquire::Retries "5";'                                                                        \
    'Acquire::http::Timeout "30";'                                                                 \
    'Acquire::https::Timeout "30";'                                                                \
    > /etc/apt/apt.conf.d/91retry-and-timeouts

RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    apt-get update &&                                                                              \
    apt-get full-upgrade -y --no-install-recommends &&                                             \
    apt-get autoremove -y --no-install-recommends &&                                               \
    apt-get autoclean -y --no-install-recommends

# Bootstrap: hardcoded so that systemDependencies.json edits don't invalidate the slow apt-source
# registration + Kitware CMake fetch below. jq is needed for extractDependencies.sh; the rest are
# the minimum set the apt-source scripts and installCMake.sh themselves require.
RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    apt-get update &&                                                                              \
    apt-get install -y --no-install-recommends                                                     \
      ca-certificates curl gnupg jq software-properties-common

RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    --mount=type=bind,src=external/infraCommons/tools,dst=/tmp/tools                               \
    bash /tmp/tools/apt/addGNUSources.sh    -y &&                                                  \
    bash /tmp/tools/apt/addLLVMSources.sh   -y &&                                                  \
    bash /tmp/tools/installCMake.sh

RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    --mount=type=bind,src=external/infraCommons/tools,dst=/tmp/tools                               \
    --mount=type=bind,src=systemDependencies.json,dst=/tmp/systemDependencies.json                 \
    apt-get update &&                                                                              \
    apt-get install -y --no-install-recommends                                                     \
      $(sh /tmp/tools/extractDependencies.sh "Basics Compilers" /tmp/systemDependencies.json)


FROM base AS dev-base
ARG TOOLCHAIN=linux-gnu-15
ENV TOOLCHAIN=${TOOLCHAIN}

RUN --mount=type=cache,target=/var/cache/apt,id=${APT_VAR_CACHE_ID},sharing=locked                 \
    --mount=type=cache,target=/var/lib/apt/lists,id=${APT_LIST_CACHE_ID},sharing=locked            \
    --mount=type=bind,src=external/infraCommons/tools,dst=/tmp/tools                               \
    --mount=type=bind,src=systemDependencies.json,dst=/tmp/systemDependencies.json                 \
    apt-get update &&                                                                              \
    apt-get install -y --no-install-recommends                                                     \
      $(sh /tmp/tools/extractDependencies.sh "Testing" /tmp/systemDependencies.json)


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
