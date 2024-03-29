#!/bin/bash

BASE="$(dirname ${BASH_SOURCE[0]})"
source $BASE/config.sh

GROUPNAME=$1

if [ "" = "$GROUPNAME" ]; then
    echo "Please specify a group name."
    exit 1
fi

if [ ! -d "$MVDS_PROJECT_BASE_DIRECTORY/src/groups" ]; then
    mkdir "$MVDS_PROJECT_BASE_DIRECTORY/src/groups"
fi

if [ -d "$MVDS_PROJECT_BASE_DIRECTORY/src/groups/$GROUPNAME" ]; then
    echo "Group $GOUPNAME already exists."
    exit 1
fi

mkdir "$MVDS_PROJECT_BASE_DIRECTORY/src/groups/$GROUPNAME"
mkdir "$MVDS_PROJECT_BASE_DIRECTORY/src/groups/$GROUPNAME/group"

$BASE/gen_group_cmakelists.sh $GROUPNAME > "$MVDS_PROJECT_BASE_DIRECTORY/src/groups/$GROUPNAME/CMakeLists.txt"
