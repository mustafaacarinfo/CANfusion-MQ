#!/usr/bin/env bash
set -e

# build klasörü yoksa yarat
[ -d build ] || mkdir build
cd build

# cmake: native build, toolchain yok
cmake .. -DCMAKE_BUILD_TYPE=Release

# derle
cmake --build . -j$(nproc)
