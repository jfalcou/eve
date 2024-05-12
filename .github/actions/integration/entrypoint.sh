#!/bin/sh -l
set -e

# ID for various tests
INSTALL_TEST=0
FETCH_TEST=1
CPM_TEST=2
MULTIARCH_TEST=3

if [ $2 -eq $INSTALL_TEST ]
then
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
  echo "::endgroup::"
fi

if [ $2 -eq $FETCH_TEST ]
then
  echo "::group::Test EVE via FetchContent"
  mkdir fetch-test && cd fetch-test
  cmake ../test/integration/fetch-test -G Ninja -DEVE_SHA1=$1
  ninja test_eve
  ./test_eve
  echo "::endgroup::"
fi

if [ $2 -eq $CPM_TEST ]
then
  echo "::group::Test EVE via CPM"
  mkdir cpm-test && cd cpm-test
  cmake ../test/integration/cpm-test -G Ninja -DEVE_SHA1=$1
  ninja test_eve
  ./test_eve
  echo "::endgroup::"
fi


if [ $2 -eq $MULTIARCH_TEST ]
then
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
