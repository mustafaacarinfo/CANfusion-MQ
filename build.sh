#!/usr/bin/env bash
set -e

BUILD_DIR=build

if [ "$1" = "pi" ]; then
  echo ">>> Pi için cross-compile"
  cmake_args="-DBUILD_FOR_PI=ON"
else
  echo ">>> Host için native build"
  cmake_args=""
fi

rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR && cd $BUILD_DIR

cmake .. -DCMAKE_BUILD_TYPE=Release $cmake_args
cmake --build . -j$(nproc)
