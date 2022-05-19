#!/usr/bin/bash

# CMake cannot add parent directiories, so this is a dirty hack
# We copy CBE into this folder, then delete it
if [[ ! -f ./thirdparty ]]
then
    mkdir -pv thirdparty/CoffeeBean
    cp -r ../../include thirdparty/CoffeeBean/include
    cp -r ../../src thirdparty/CoffeeBean/src
    cp -r ../../thirdparty thirdparty/CoffeeBean/thirdparty
    cp -r ../../cmake thirdparty/CoffeeBean/cmake
    cp ../../CMakeLists.txt thirdparty/CoffeeBean/CMakeLists.txt
fi

mkdir -pv build
cmake -S . -B build
cd build
make
cd ..
