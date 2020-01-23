#!/bin/bash

# exit script on any error
set -e
set -o xtrace

PROJECT_DIR=$(pwd)
INSTALL_PATH=$PROJECT_DIR/../tmp/usr
mkdir -p $INSTALL_PATH

# Configure Project
mkdir -p $PROJECT_DIR/build
cd $PROJECT_DIR/build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DBITMAP_BUILD_EXAMPLES=ON -DBITMAP_BUILD_TESTS=ON ..

# Build test
make -j 32

# Run tests
test/tests

# Install
make install

# Check install
git diff --no-index $INSTALL_PATH/include/bitmap $PROJECT_DIR/include/bitmap
test -f $INSTALL_PATH/lib/cmake/bitmap/bitmap-config.cmake

# Check install by example project
mkdir -p $PROJECT_DIR/build-package-test
cd $PROJECT_DIR/build-package-test
cmake -DCMAKE_PREFIX_PATH=$INSTALL_PATH ../test-package
make -j 32
./test_bitmap_package
