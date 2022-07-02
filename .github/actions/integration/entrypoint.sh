#!/bin/sh -l
set -e

echo "::group::Configure EVE"
mkdir build && cd build
cmake .. -G Ninja
echo "::endgroup::"

echo "::group::Install EVE"
ninja install | grep cmake
cd ..
echo "::endgroup::"

echo "::group::Compile EVE-dependent project"
mkdir install-test && cd install-test
cmake ../integration/install-test -G Ninja
ninja test_eve
./test_eve
echo "::endgroup::"

return 0;
