#!/bin/bash

# exit script on any error
set -e
set -o xtrace

git submodule sync --recursive
git submodule update --init --recursive
