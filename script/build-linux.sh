#!/bin/bash

# exit script on any error
set -e
set -o xtrace

PROJECT_DIR=$(pwd)
mkdir -p /mnt/install

# Configure Project
mkdir -p /mnt/build
cd /mnt/build
cmake $CMAKE_VARS -DCMAKE_INSTALL_PREFIX=/mnt/install -DBITMAP_BUILD_TESTS=ON $PROJECT_DIR

# Build test
make -j $(nproc)

# Run tests
test/tests

# Install
make install

# Check install
git diff --no-index /mnt/install/include $PROJECT_DIR/include
test -f /mnt/install/lib/cmake/bitmap/bitmap-config.cmake

# Check install by example project
mkdir -p /mnt/build-package-test
cd /mnt/build-package-test
cmake $CMAKE_VARS -DCMAKE_PREFIX_PATH=/mnt/install $PROJECT_DIR/test-package
make -j $(nproc)
./test_bitmap_package
