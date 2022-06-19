#!/bin/sh -l
set -e
echo "::group:: Running: 'cmake .. -G Ninja -DCMAKE_CXX_FLAGS="$1" $2'"
mkdir build
cd build
cmake .. -G Ninja -DEVE_OPTIONS="$1" $2
echo "::endgroup::"

echo "::group:: Compiling Unit Tests"
ninja -v unit -j 8
echo "::endgroup::"

echo "::group:: Running Unit Tests"
ctest --output-on-failure -j 8
echo "::endgroup::"

exit 0
