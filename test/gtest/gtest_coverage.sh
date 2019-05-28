#!/bin/sh

if [ -e product ]; then
    cd product
fi

set -eu

rm -rf build
mkdir build
cd build


cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .
export GTEST_COLOR=1
make test_coverage