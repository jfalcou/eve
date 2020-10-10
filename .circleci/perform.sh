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
## Run every test up to SIMD
##==================================================================================================
ninja unit.arch.exe -k 0      && ctest -R "^unit.arch\..*\.exe"               && \
ninja unit.api.exe  -k 0 -j 8 && ctest -R "^unit.api\..*\.exe"          -j 8  && \
ninja doc.exe       -k 0 -j 8 && ctest -R "^doc\..*\.exe"               -j 8  && \
ninja unit.simd.exe -k 0 -j 2 && ctest -R "^unit\..*\..*\..*\.simd.exe" -j 8
