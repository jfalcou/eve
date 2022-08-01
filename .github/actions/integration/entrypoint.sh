#!/bin/sh -l
set -e

# Setup github/worspace as safe
git config --global --add safe.directory /github/workspace

# ID for various tests
INSTALL_TEST=0
FETCH_TEST=1
CPM_TEST=2
MULTIARCH_TEST=3

configure_and_ctest() {
  test_regex=$1

  cmake -B build -S . -G Ninja \
    -DEVE_BUILD_INTEGRATION=ON \
    -DEVE_BUILD_TEST=OFF       \
    -DEVE_BUILD_DOCUMENTATION=OFF

  # eve build not required: cmake --build build
  ctest --test-dir build --output-on-failure -R $test_regex
}

if [ $2 -eq $INSTALL_TEST ]; then
  echo "::group::Prepare EVE repository for branch " $1
  configure_and_ctest integration.install-eve.exe
  echo "::endgroup::"

  echo "::group::Test EVE via the install target"
  ctest --test-dir build --output-on-failure -R integration.install.exe
  echo "::endgroup::"
fi

if [ $2 -eq $FETCH_TEST ]; then
  echo "::group::Test EVE via FetchContent"
  configure_and_ctest integration.fetch.exe
  echo "::endgroup::"
fi

if [ $2 -eq $CPM_TEST ]; then
  echo "::group::Test EVE via CPM"
  configure_and_ctest integration.cpm.exe
  echo "::endgroup::"
fi

if [ $2 -eq $MULTIARCH_TEST ]; then
  echo "::group::Prepare EVE repository for branch " $1
  mkdir build && cd build
  cmake .. -G Ninja
  ninja install > /dev/null
  CURRENT_SHA1=`git rev-parse HEAD`
  cd ..
  echo "::endgroup::"

  echo "::group::Test EVE multi-architecture support"
  mkdir multi-test && cd multi-test
  cmake ../examples/multi-arch -G Ninja
  ninja multi-arch
  ./multi-arch
  echo "::endgroup::"
fi

return 0;
