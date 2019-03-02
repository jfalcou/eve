##==================================================================================================
##  TTS - Tiny Test System
##  Copyright 2019 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

mkdir -p build
cd build

$1 --version
cmake .. -DCMAKE_BUILD_TYPE=$VARIANT -G Ninja -DCMAKE_CXX_COMPILER=$1 -DCMAKE_CXX_FLAGS=$OPTIONS
ninja unit -j 8
ctest -D Experimental -j 8
