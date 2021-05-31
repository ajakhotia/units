#!/bin/sh

usage()
{
    echo "Argument for install prefix is required. Please invoke the command as follows:"
    echo "${0} /path/to/install/dir"
    echo "NOTE: Ensure that you have permission to write to the specified directory."
}

if [ -z "$1" ]; then
    usage
    exit 1
fi

INSTALL_PREFIX=$1

# Download the robotFarm archive and extract it to /tmp
curl -L https://github.com/ajakhotia/robotFarm/archive/v0.1.0.tar.gz -o /tmp/robotFarm.tar.gz || exit
cmake -E chdir /tmp cmake -E tar -x /tmp/robotFarm.tar.gz  || exit
cmake -E remove_directory /tmp/robotFarm-src  || exit
cmake -E rename /tmp/robotFarm-0.1.0 /tmp/robotFarm-src  || exit
cmake -E remove /tmp/robotFarm.tar.gz  || exit
cmake -E make_directory /tmp/robotFarm-build  || exit

# Configure the robotFarm project using Ninja as the generator.
# Here we will configure robotFarm to build gtest
cmake -G Ninja -S /tmp/robotFarm-src -B /tmp/robotFarm-build    \
    -DCMAKE_BUILD_TYPE:STRING="Release"                         \
    -DCMAKE_INSTALL_PREFIX:PATH="${INSTALL_PREFIX}"             \
    -DROBOT_FARM_BUILD_GOOGLE_TEST:BOOL=ON  || exit

# Build and install robotFarm to user specified directory.
cmake --build /tmp/robotFarm-build --config Release --parallel "$(nproc)" || exit
cmake --install /tmp/robotFarm-build --config Release || exit