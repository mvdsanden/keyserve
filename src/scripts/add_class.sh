#!/bin/bash

BASE="$(dirname ${BASH_SOURCE[0]})"
source $BASE/config.sh

CLASSNAME=$1

if [ "" = "$CLASSNAME" ]; then
    echo "Please specify a class name."
    exit 1
fi

addGroupClass(){

    GROUPNAME=$1
    PKGNAME=$2
    
    if [ "" = "$GROUPNAME" ] || [ "" = "$PKGNAME" ]; then
	echo "Please run this script in the package root directory."
	exit 2
    fi

    echo "Adding group class"
    
    NAMEBASE="${PKGNAME,,}_${CLASSNAME,,}"
    
    if grep -xq "$NAMEBASE" package/members; then
	echo "Class $CLASSNAME is already a member of $GROUPNAME."
	exit 3
    fi

    echo $NAMEBASE >> package/members
    
    echo "Creating class $ROOT_NS::$GROUPNAME::$PKGNAME::$CLASSNAME"
    $BASE/gen_header.sh $ROOT_NS $PKGNAME $CLASSNAME > "${PKGNAME,,}_${CLASSNAME,,}.h"
    $BASE/gen_source.sh $ROOT_NS $PKGNAME $CLASSNAME > "${PKGNAME,,}_${CLASSNAME,,}.cpp"
    $BASE/gen_test.sh $ROOT_NS $PKGNAME $CLASSNAME > "${PKGNAME,,}_${CLASSNAME,,}.g.cpp"
}

addAdapterClass(){

    ADAPTERNAME=$1

    if [ "" = "$ADAPTERNAME" ]; then
	echo "Please run this script in the adapter root directory."
	exit 2
    fi

    NAMEBASE="${ADAPTERNAME,,}_${CLASSNAME,,}"
    
    if grep -xq "$NAMEBASE" adapter/members; then
	echo "Class $CLASSNAME is already a member of $ADAPTERNAME."
	exit 3
    fi

    echo $NAMEBASE >> adapter/members
    
    echo "Creating class $ROOT_NS::$ADAPTERNAME::$CLASSNAME"
    $BASE/gen_header.sh $ROOT_NS $ADAPTERNAME $CLASSNAME > "${ADAPTERNAME,,}_${CLASSNAME,,}.h"
    $BASE/gen_source.sh $ROOT_NS $ADAPTERNAME $CLASSNAME > "${ADAPTERNAME,,}_${CLASSNAME,,}.cpp"
    $BASE/gen_test.sh $ROOT_NS $ADAPTERNAME $CLASSNAME > "${ADAPTERNAME,,}_${CLASSNAME,,}.g.cpp"
}

addApplicationClass(){

    APPLICATIONNAME=$1

    if [ "" = "$APPLICATIONNAME" ]; then
	echo "Please run this script in the application root directory."
	exit 2
    fi

    NAMEBASE="${APPLICATIONNAME,,}_${CLASSNAME,,}"
    
    if grep -xq "$NAMEBASE" application/members; then
	echo "Class $CLASSNAME is already a member of $APPLICATIONNAME."
	exit 3
    fi

    echo $NAMEBASE >> application/members
    
    echo "Creating class $ROOT_NS::$APPLICATIONNAME::$CLASSNAME"
    $BASE/gen_header.sh $ROOT_NS $APPLICATIONNAME $CLASSNAME > "${APPLICATIONNAME,,}_${CLASSNAME,,}.h"
    $BASE/gen_source.sh $ROOT_NS $APPLICATIONNAME $CLASSNAME > "${APPLICATIONNAME,,}_${CLASSNAME,,}.cpp"
    $BASE/gen_test.sh $ROOT_NS $APPLICATIONNAME $CLASSNAME > "${APPLICATIONNAME,,}_${CLASSNAME,,}.g.cpp"
}


if pwd | egrep -q "/groups/[^/]*/[^/]*"; then
    addGroupClass $(pwd | sed -e 's|^.*/groups/\([^/]*\)/\([^/]*\)$|\1 \2|')
fi

if pwd | egrep -q "/adapters/[^/]*"; then
    addAdapterClass $(pwd | sed -e 's|^.*/adapters/\([^/]*\)$|\1|')
fi

if pwd | egrep -q "/applications/[^/]*"; then
    addApplicationClass $(pwd | sed -e 's|^.*/applications/\([^/]*\)$|\1|')
fi



