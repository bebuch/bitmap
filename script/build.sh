#!/bin/bash

if [ $# -lt 1 ] || [ "$1" != "linux" ] && [ "$1" != "windows" ]; then
    echo "Usage: $0 OS"
    echo "    where OS is linux or windows"
    exit 1
fi

echo "Build for $1"

# exit script on any error
set -e
set -o xtrace

# build
PROJECT_DIR=$(pwd)
mkdir -p /mnt/install

# Configure Project
mkdir -p /mnt/build
cd /mnt/build
cmake $CMAKE_VARS -DCMAKE_INSTALL_PREFIX=/mnt/install -DBITMAP_BUILD_TESTS=ON $PROJECT_DIR
cmake --build . --parallel
ctest
cmake --install .

# Check install
git diff --no-index /mnt/install/include $PROJECT_DIR/include
test -f /mnt/install/lib/cmake/bitmap/bitmapTargets.cmake
test -f /mnt/install/lib/cmake/bitmap/bitmapConfig.cmake
test -f /mnt/install/lib/cmake/bitmap/bitmapConfigVersion.cmake

# Check install by example project
mkdir -p /mnt/build-package-test
cd /mnt/build-package-test
cmake $CMAKE_VARS -DCMAKE_PREFIX_PATH=/mnt/install $PROJECT_DIR/test-package
cmake --build . --parallel
ctest
