#!/bin/sh

set -eu

if [ -e product ]; then
    cd product
fi

cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
