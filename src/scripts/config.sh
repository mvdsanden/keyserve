#!/bin/bash

ROOT_NS="MvdS"

MVDS_PROJECT_BASE_DIRECTORY=$(git rev-parse --show-toplevel)

echo "Project base directory: $MVDS_PROJECT_BASE_DIRECTORY"

CLANG_FORMAT=clang-format-7
