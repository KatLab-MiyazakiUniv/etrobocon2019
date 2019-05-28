#!/bin/sh

set -eu

if [ -e product ]; then
    cd product
fi

cd build

cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .

export GTEST_COLOR=1
ctest -VV
