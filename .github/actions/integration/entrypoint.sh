#!/bin/sh -l
set -e

echo "::group::Prepare EVE repository for branch " $1
mkdir build && cd build
cmake .. -G Ninja
ninja install | grep cmake
CURRENT_SHA1=`git rev-parse HEAD`
cd ..
echo "::endgroup::"

echo "::group::Test EVE via the install target"
mkdir install-test && cd install-test
cmake ../test/integration/install-test -G Ninja
ninja test_eve
./test_eve
cd ..
echo "::endgroup::"

echo "::group::Test EVE via FetchContent"
mkdir fetch-test && cd fetch-test
cmake ../test/integration/fetch-test -G Ninja -DEVE_SHA1=$1
ninja test_eve
./test_eve
cd ..
echo "::endgroup::"

echo "::group::Test EVE via CPM"
mkdir cpm-test && cd cpm-test
cmake ../test/integration/cpm-test -G Ninja -DEVE_SHA1=$1
ninja test_eve
./test_eve
cd ..
echo "::endgroup::"

return 0;
