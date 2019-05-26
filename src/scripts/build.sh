#!/bin/bash

BASE="$(dirname ${BASH_SOURCE[0]})"
source $BASE/config.sh

if [ ! -d "$MVDS_PROJECT_BASE_DIRECTORY/bld" ]; then
    mkdir "$MVDS_PROJECT_BASE_DIRECTORY/bld"
fi

pushd "$MVDS_PROJECT_BASE_DIRECTORY/bld"

cmake "$MVDS_PROJECT_BASE_DIRECTORY/src"
make -j8
