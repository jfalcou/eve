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
## Compile every test for SIMD
## We keep compiling even with errors as we want the most test being run
##==================================================================================================
ninja arch.unit  -k 0 -j 8
ninja meta.unit  -k 0 -j 8
ninja doc.unit   -k 0 -j 8
ninja api.unit   -k 0 -j 8

##==================================================================================================
## Run every tests for SIMD
##==================================================================================================
ctest -R ^arch.*.unit -j 8 && ctest -R ^meta.*.unit -j 8 && \
ctest -R ^doc.*.unit  -j 8 && ctest -R ^api.*.unit  -j 8
