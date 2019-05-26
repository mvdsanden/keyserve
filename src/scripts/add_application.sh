#!/bin/bash

BASE="$(dirname ${BASH_SOURCE[0]})"
source $BASE/config.sh

APPNAME=$1

if [ "" = "$APPNAME" ]; then
    echo "Please specify an application name."
    exit 1
fi

if [ ! -d "$MVDS_PROJECT_BASE_DIRECTORY/src/applications" ]; then
    mkdir "$MVDS_PROJECT_BASE_DIRECTORY/src/applications"
fi

if [ -d "$MVDS_PROJECT_BASE_DIRECTORY/src/applications/$APPNAME" ]; then
    echo "Application $APPNAME already exists."
    exit 1
fi

mkdir "$MVDS_PROJECT_BASE_DIRECTORY/src/applications/$APPNAME"
mkdir "$MVDS_PROJECT_BASE_DIRECTORY/src/applications/$APPNAME/application"

$BASE/gen_application_main.sh > "$MVDS_PROJECT_BASE_DIRECTORY/src/applications/$APPNAME/$APPNAME.m.cpp"

echo $APPNAME.m >> "$MVDS_PROJECT_BASE_DIRECTORY/src/applications/$APPNAME/application/members"


$BASE/gen_application_cmakelists.sh $APPNAME > "$MVDS_PROJECT_BASE_DIRECTORY/src/applications/$APPNAME/CMakeLists.txt"
