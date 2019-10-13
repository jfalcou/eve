##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

##==================================================================================================
## Prepare variant's folder
##==================================================================================================
mkdir -p build/$VARIANT
cd build/$VARIANT

##==================================================================================================
## CMAKE
##==================================================================================================
if [[ -v RUN_COMMAND ]]
then
  echo "Running tests with $RUN_COMMAND ..."
  cmake ../.. -G Ninja $CMAKE_OPTIONS -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS" -DCMAKE_CROSSCOMPILING_CMD="$RUN_COMMAND"
else
  cmake ../.. -G Ninja $CMAKE_OPTIONS -DCMAKE_CXX_COMPILER="$COMPILER" -DCMAKE_CXX_FLAGS="$OPTIONS"
fi

##==================================================================================================
## PATH Infos
##==================================================================================================
if [[ -v EXTRA_PATH ]]
then
  echo "Updating path for $EXTRA_PATH/$EXTRA_NAME ..."
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$EXTRA_PATH
  export LD_LIBRARY_PATH
  ln -sf $EXTRA_PATH/$EXTRA_NAME /$EXTRA_LIB/$EXTRA_NAME
fi

##==================================================================================================
## Run every test up to SIMD
##==================================================================================================
ninja arch.unit         -j 8 && ctest -R ^arch.*.unit           -j 8 && \
ninja meta.unit         -j 8 && ctest -R ^meta.*.unit           -j 8 && \
ninja doc.unit          -j 8 && ctest -R ^doc.*.unit            -j 8 && \
ninja api.unit          -j 8 && ctest -R ^api.*.unit            -j 8 && \
ninja core.scalar.unit  -j 8 && ctest -R ^core.*.scalar.*.unit  -j 8
