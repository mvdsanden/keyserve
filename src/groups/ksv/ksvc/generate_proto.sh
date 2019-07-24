#!/bin/sh

protoc --proto_path=. --cpp_out=. *.proto
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ksvc_keyserveservice.proto
