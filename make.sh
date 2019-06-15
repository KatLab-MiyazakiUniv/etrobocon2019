#!/bin/bash

set -eu

if hash docker 2>/dev/null; then
    cd src
    docker run --rm -it -v "${PWD}":/home/hrp2/sdk/workspace/product korosuke613/etrobo-docker make_src
    mv -f app ../et2019
else
    cd ..
    make app=product/src
    mv -f app product/et2019
fi
