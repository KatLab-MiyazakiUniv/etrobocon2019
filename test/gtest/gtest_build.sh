#!/bin/sh

if [ -e product ]; then
    cd product
fi

rm -rf build
mkdir build
cd build

set -eu

cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .
make
