##==================================================================================================
##  TTS - Tiny Test System
##  Copyright 2019 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

$1 --version

mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja -DCI_ENABLED=1 -DCMAKE_CXX_COMPILER=$1 -DTTS_VERSION_STRING=CircleCI
ninja unit -j 8
ctest -D Experimental -j 8