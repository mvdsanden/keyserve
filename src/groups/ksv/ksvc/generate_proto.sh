#!/bin/sh

protoc --proto_path=. --cpp_out=. *.proto
