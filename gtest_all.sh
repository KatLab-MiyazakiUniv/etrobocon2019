#!/bin/bash

set -eu

if hash docker 2>/dev/null; then
    docker run --rm -it -v "${PWD}":/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker /home/hrp2/sdk/workspace/product/test/gtest/gtest_build.sh
else
    ./test/gtest/gtest_build.sh
fi