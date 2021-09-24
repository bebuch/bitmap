#!/bin/bash
set -e        # exit script on any error
set -o xtrace # print commands in log

# add temporary credentials and check out the submodules
printf "machine gitlab.tu-ilmenau.de\nlogin gitlab-ci-token\npassword $CI_JOB_TOKEN\n" > ~/.netrc
git submodule sync --recursive
git submodule update --init --recursive
