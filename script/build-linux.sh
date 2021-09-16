#!/bin/bash

# exit script on any error
set -e
set -o xtrace

PROJECT_DIR=$(pwd)
mkdir -p /mnt/install

# Configure Project
mkdir -p /mnt/build
cd /mnt/build
cmake $CMAKE_VARS -DCMAKE_INSTALL_PREFIX=/mnt/install -DBITMAP_BUILD_EXAMPLES=ON -DBITMAP_BUILD_TESTS=ON $PROJECT_DIR

# Build test
make -j 32

# Run tests
test/tests

# Install
make install

# Check install
git diff --no-index /mnt/install/include/bitmap $PROJECT_DIR/include/bitmap
test -f /mnt/install/lib/cmake/bitmap/bitmap-config.cmake

# Check install by example project
mkdir -p /mnt/build-package-test
cd /mnt/build-package-test
cmake $CMAKE_VARS -DCMAKE_PREFIX_PATH=/mnt/install $PROJECT_DIR/test-package
make -j 32
./test_bitmap_package
