#!/bin/bash

BASE="$(dirname $0)"
source $BASE/config.sh

export PATH=$MVDS_PROJECT_BASE_DIRECTORY/src/scripts/:$PATH
