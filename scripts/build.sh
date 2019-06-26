#!/bin/bash

# exit script on any error
set -e
set -o xtrace

# create build dir
mkdir build
cd build

# build
cmake ..
make

# unit tests
test/test/bitmap_lib_tests

# clean up
cd ..
rm -r build
