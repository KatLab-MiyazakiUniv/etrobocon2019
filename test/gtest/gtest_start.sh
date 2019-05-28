#!/bin/sh

set -eu

if [ -e product ]; then
    cd product
fi

cmake --build .
make