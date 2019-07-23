# Keyserve
Straightforward Key Management Service

When finished, this will be a KMS that is able to manage symetric and asymmetric
encryption keys. It will be loosely based on the Google Gloud Key management
api.

## Project structure

The project is subdivided into the following directories:

* */src/scripts:* Helper scripts for the project.
* */src/modules:* Cmake modules.
* */src/applications/$application:* Source code for separate applications.
* */src/adapters/$adapter:* Source code for adapter libraries.
* */src/groups:* Package groups.
* */src/groups/$package/*: Source code for packages.
* */src/thirdparty/*: Thirdparty libraries.

Both adapters ad package groups will be compiled into separate libraries,
which are statically linked into the applications that depend on them.

## Cloning

```
git clone $repo/keyserve
cd keyserve
git submodule update --init
```

## Building

Building is done using cmake.

```
mkdir bld
cd bld
cmake ../src
make -j8
```

If the protobuf files have compilation errors, this is because your protobuf libraries
are from a different version of protobuf. Please do the following then:

```
cd src/groups/ksv/ksvc
./generate_proto.sh
```

### Dependencies

#### G++-8

Since I'm using the C++17 please use g++-8 for compiling.

#### Protobuf

As I am planning to use gRPC I compiled and installed a recent stable version of gRPC
as well as its companion protobuf library.
