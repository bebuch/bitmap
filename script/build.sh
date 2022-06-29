#!/bin/bash

# exit script on any error
set -e
set -o xtrace

# build
PROJECT_DIR=$(pwd)
PROJECT_NAME=$(basename $(git remote get-url origin) .git)
mkdir -p /mnt/install

# Configure Project
mkdir -p /mnt/build && cd $_
cmake -C /etc/TargetOS.cmake -DCMAKE_INSTALL_PREFIX=/mnt/install -DBUILD_TESTING=ON $PROJECT_DIR
cmake --build . --parallel $(nproc)
ctest --output-on-failure --parallel $(nproc)
cmake --install .

# Check install
git diff --no-index /mnt/install/include $PROJECT_DIR/include
test -f /mnt/install/lib/cmake/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake
test -f /mnt/install/lib/cmake/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
test -f /mnt/install/lib/cmake/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake

# Check install by example project
mkdir -p /mnt/build_package_test && cd $_
cmake -C /etc/TargetOS.cmake -DCMAKE_PREFIX_PATH=/mnt/install $PROJECT_DIR/test_package
cmake --build . --parallel
ctest --output-on-failure --parallel $(nproc)
