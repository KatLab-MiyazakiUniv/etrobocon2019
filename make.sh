#!/bin/bash

set -eu

cd src
docker run --rm -it -v "${PWD}":/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker make_src
mv app ../et2019