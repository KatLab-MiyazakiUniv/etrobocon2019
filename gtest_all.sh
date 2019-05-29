#!/bin/bash

set -eu

docker run --rm -it -v "${PWD}":/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker /home/hrp2/sdk/workspace/product/test/gtest/gtest_build.sh
