#!/bin/bash
set -e

echo "Building Taiko Clone..."

mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

echo ""
echo "Build complete! Run with: ./build/taiko"