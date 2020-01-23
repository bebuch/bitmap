#!/bin/bash
set -e        # exit script on any error
set -o xtrace # print commands in log

# add temporary credentials and check out the submodules
printf "machine gitlab.tu-ilmenau.de\nlogin gitlab-ci-token\npassword $CI_JOB_TOKEN\n" > ~/.netrc
git submodule sync --recursive
git submodule update --init --recursive

# build and install dependencies
PROJECT_DIR=$(pwd)

mkdir -p $PROJECT_DIR/3rdparty/io_tools/build
cd $PROJECT_DIR/3rdparty/io_tools/build
cmake ..
make -j 32
make install

mkdir -p $PROJECT_DIR/3rdparty/colormap/build
cd $PROJECT_DIR/3rdparty/colormap/build
cmake ..
make -j 32
make install
