#!/bin/bash

BASE="$(dirname ${BASH_SOURCE[0]})"
source $BASE/config.sh

export PATH=$MVDS_PROJECT_BASE_DIRECTORY/src/scripts/:$PATH
